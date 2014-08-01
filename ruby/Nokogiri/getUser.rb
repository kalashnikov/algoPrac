#!/usr/local/rvm/rubies/ruby-2.0.0-p247/bin/ruby
require 'nokogiri'
require 'open-uri'
require 'openssl'
require 'mongo'
include Mongo
#
# This script get Douban movie watch list and save into MongoDB
# Example: http://movie.douban.com/people/kalashnikov/collect
# 

DEBUG = false 

# Setting for MongoDB
$db = MongoClient.new("localhost", 27017).db("kala")
$auth = $db.authenticate(ENV['MONGO_ACCOUNT'],ENV['MONGO_PASSWORD'])
$coll = $db["user"]
$mcoll = $db["movie"]

$rateData = Hash.new

def getUserMovieRate(url)
    
    # Clear Rate Data 
    $rateData.clear
    
    page = Nokogiri::HTML(open(url, "Accept" => "text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8",
                               "Accept-Language" => "zh-TW,zh;q=0.8,en;q=0.6,en-US;q=0.4",
                               "Connection" => "keep-alive",
                               "User-Agent" => "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_9_2) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/34.0.1847.137 Safari/537.36"
                              ))
    page.encoding = 'utf-8'

    max = 0 
    page.css('div.paginator a').each do |l|

        # Get the max number of movie list
        link = l['href']
        num  = /collect\?start=(\d+)&/.match(link)[1].to_i
        max  = num if num > max
    end

    # Parse first page
    extractData(page)

    (15..max).step(15).each do |i|
        link = "#{url}?start=#{i}&amp;sort=time&amp;rating=all&amp;filter=all&amp;mode=grid"
        page = Nokogiri::HTML(open(link, "Accept" => "text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8",
                                   "Accept-Language" => "zh-TW,zh;q=0.8,en;q=0.6,en-US;q=0.4",
                                   "Connection" => "keep-alive",
                                   "User-Agent" => "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_9_2) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/34.0.1847.137 Safari/537.36"
                                  ))
        page.encoding = 'utf-8'
        extractData(page)
        
        if i%900==0
            print "\n### Wait 30 secs ... ###\n"
            sleep(30)
        end
    end
end

# Extract user info
def extractData(page)
    page.css('div.item').each do |it|
       
        title  = it.css('li.title a em').text
        mdate1 = it.css('li.intro').text.split('/')[0]
        imgsrc = it.css('div.pic a img')[0]['src']
        link   = it.css('li.title a')[0]['href']

        begin 
            rat = it.css('div.info li')[2].css('span')[0][:class]
            
            # Condition checking, may not have rating 
            idx1   = !rat.include?("rating") ? 0 : 1
            idx2   = !rat.include?("rating") ? 2 : 3

            date   = it.css('div.info li')[2].css('span')[idx1].text
            comment= it.css('div.info li')[3].css('span')[0].text if it.css('div.info li').size>idx2 and it.css('div.info li')[3]

            mdate2 = (mdate1.include?('(')) ? mdate1.split('(')[0] : mdate1

            # Get date from detail page
            if !mdate2.include?('-') and mdate2.size>4
                begin
                    dpage = Nokogiri::HTML(open(link, "Accept" => "text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8",
                                                "Accept-Language" => "zh-TW,zh;q=0.8,en;q=0.6,en-US;q=0.4",
                                                "Connection" => "keep-alive",
                                                "User-Agent" => "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_9_2) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/34.0.1847.137 Safari/537.36"
                                               ))
                rescue
                    mdate2 = "1000-01-01"
                else
                    dpage.encoding = 'utf-8'
                    mdate2 = dpage.css('span[@class="year"]').text[1..4]
                end
            end

            mdate2 = "1000-01-01" if !mdate2 or /^\D+/.match(mdate2.chomp)

        rescue
            rat     = "rating0"
            mdate2  = "1000-01-01"
            comment = ""
        end
       
        did    = /subject\/(\d+)\//.match(link)[1]    
        rating = (DEBUG) ? rat[6].to_i : 0
        begin 
            if mdate2.include?('-') 
                if mdate2.count('-')==2
                    dateutc = DateTime.strptime(mdate2, '%Y-%m-%d').to_time.utc
                elsif mdate2.count('-')==1
                    dateutc = DateTime.strptime(mdate2, '%Y-%m').to_time.utc
                else mdate2.size>4
                    dateutc = DateTime.strptime(mdate2[0..3], '%Y').to_time.utc
                end
            else
                dateutc = DateTime.strptime(mdate2, '%Y').to_time.utc
            end
        rescue
            puts mdate2
        end

        p "#{did} #{rating} #{dateutc} | #{title} | #{comment}"

        doc = { "id" => did.to_i,
                "title" => title,
                "imgsrc" => imgsrc,
                "link" => link,
                "rating" => rating,
                "date" => dateutc
                #"comment" => comment
        }

        result = $mcoll.find("id" => did.to_i)
        if !result or result.count==0
            $mcoll.insert(doc)
        else
            result.each do |r|
                oldData = r
                oldData.merge(doc)
                $mcoll.update({"id" => did.to_i}, oldData)
            end
        end
        $rateData[did]=rating
    end
end

# Extract user info
def extractSimpleInfo(page)
    page.css('div.pic').each do |it|
       
        name   = it.css('a img')[0]['alt']
        imgsrc = it.css('a img')[0]['src']
        link   = it.css('a')[0]['href']
        uid    = link.split('/').last

        next if !link.include?("people")

        p "#{uid} #{name} #{imgsrc} | #{link}"

        doc = { "id" => uid,
                "name" => name,
                "imgsrc" => imgsrc,
                "link" => link
        }

        result = $coll.find("id" => uid)
        if !result
            $coll.insert(doc)
        else 
            result.each do |r|
                oldData = r
                oldData.merge(doc)
                $coll.update({"id" => uid}, oldData)
            end
        end
    end
end

def getUserByGroup(url)
    page = Nokogiri::HTML(open(url, "Accept" => "text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8",
                               "Accept-Language" => "zh-TW,zh;q=0.8,en;q=0.6,en-US;q=0.4",
                               "Connection" => "keep-alive",
                               "User-Agent" => "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_9_2) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/34.0.1847.137 Safari/537.36"
                              ))
    page.encoding = 'utf-8'

    max = 0 
    page.css('div.paginator a').each do |l|

        # Get the max number of movie list
        link = l['href'] 
        num  = /members\?start=(\d+)/.match(link)[1].to_i
        max  = num if num > max
    end

    # Parse first page
    extractSimpleInfo(page)

    (35..max).step(35).each do |i|
        link = "#{url}?start=#{i}"
        page = Nokogiri::HTML(open(link, "Accept" => "text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8",
                                   "Accept-Language" => "zh-TW,zh;q=0.8,en;q=0.6,en-US;q=0.4",
                                   "Connection" => "keep-alive",
                                   "User-Agent" => "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_9_2) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/34.0.1847.137 Safari/537.36"
                                  ))
        page.encoding = 'utf-8'
        extractSimpleInfo(page)

        if i%700==0
            print "\n### Wait 30 secs ... ###\n"
            sleep(30)
        end
    end
end

def getUserIdList(link)
    page  = Nokogiri::HTML(open(link, "Accept" => "text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8",
                                "Accept-Language" => "zh-TW,zh;q=0.8,en;q=0.6,en-US;q=0.4",
                                "Connection" => "keep-alive",
                                "User-Agent" => "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_9_2) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/34.0.1847.137 Safari/537.36"
                               ))
    page.encoding = 'utf-8'

    list = []
    page.css('div.clear dl.obu').each do |it|
        name   = it.css('a img')[0]['alt']
        imgsrc = it.css('a img')[0]['src']
        link   = it.css('a')[0]['href']
        uid    = link.split('/').last

        next if !link.include?("people")

        p "#{uid} #{name} #{imgsrc} | #{link}"

        list.push(uid)
=begin
        doc = { "id" => uid,
                "name" => name,
                "imgsrc" => imgsrc,
                "link" => link
        }

        result = $coll.find("id" => uid, :limit=>1 )
        if !result or !result.first
            $coll.insert(doc)
        else 
            doc = result.first
            doc["desc"] = @desc
            doc["rate"] = $rateData
            $coll.update({"id" => uid}, doc)
        end   
=end
    end
    return list
end

def updateUserInfo(id)
    link  = "http://www.douban.com/people/#{id}/"
    mlink = "http://movie.douban.com/people/#{id}/collect"
    wLink = "http://www.douban.com/people/#{id}/contacts"
    fLink = "http://www.douban.com/people/#{id}/rev_contacts"

    begin
        page  = Nokogiri::HTML(open(link, "Accept" => "text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8",
                                   "Accept-Language" => "zh-TW,zh;q=0.8,en;q=0.6,en-US;q=0.4",
                                   "Connection" => "keep-alive",
                                   "User-Agent" => "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_9_2) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/34.0.1847.137 Safari/537.36"
                                  ))
    rescue
        puts "### Error with Link:#{link}"
        sleep(20)
        retry
    end

    page.encoding = 'utf-8'
    @desc = page.css('span[@id="intro_display"]').text

    # Check Contact need login
    #@watchList    = getUserIdList(wLink)
    #@followerList = getUserIdList(fLink)
    
    result = $coll.find("id" => id)

    if !result
        return 
        $coll.insert(doc)
    else
        # Update should based on previous data
        result.each do |r|
            oldData = r

            # Get Movie Rate
            getUserMovieRate(mlink) 
            
            oldData.merge(r)
            oldData["desc"] = @desc
            oldData["rate"] = $rateData
            oldData["checked"] = 1 
            $coll.update({"id" => id}, oldData)

            print "\n### Wait ... ###\n"
            if $rateData.size>60 
                sleep($rateData.size/20)
            else 
                sleep(10)
            end
        end
    end
end

def doTask()

    # Movie Group 
    #$url="http://www.douban.com/group/447473/members"
    #$url="http://www.douban.com/group/202728/members"
    #$url="http://www.douban.com/group/ThirdWorldMovie/members"
    #$url="http://www.douban.com/group/213478/members"
    #getUserByGroup($url)

    # Update User Info
    #id    = "shu_shu"
    #id    = "kalashnikov"
    begin
        $coll.find({}).each do |u|

            next if u["checked"]==1

            id = u["id"]
            puts "### Get User: #{id}"

            updateUserInfo(id)
        end        
    rescue
        sleep(70)
        retry
    end


    total = $coll.find({}).count
    puts "### Current Total User: #{total}" 

    total = $mcoll.find({}).count
    puts "### Current Total Movie: #{total}" 
end

doTask
