#!/usr/local/rvm/rubies/ruby-2.0.0-p247/bin/ruby
require 'nokogiri'
require 'open-uri'
require 'openssl'
require 'mongo'
require 'csv'
require 'set'
include Mongo
#
# This script get Douban movie watch list and save into MongoDB
# Example: http://movie.douban.com/people/kalashnikov/wish
# 

# Setting for MongoDB
$db = MongoClient.new("localhost", 27017).db("kala")
$auth = $db.authenticate(ENV['MONGO_ACCOUNT'],ENV['MONGO_PASSWORD'])
$coll = $db["movieWish"]

# Extract movie info
def extractData(page)
    page.css('div.item').each do |it|
       
        title  = it.css('li.title a em').text
        mdate1 = it.css('li.intro').text.split('/')[0]
        imgsrc = it.css('div.pic a img')[0]['src']
        link   = it.css('li.title a')[0]['href']
        rat    = it.css('div.info li')[2].css('span')[0][:class]
        
        # Condition checking, may not have rating 
        idx1   = !rat.include?("rating") ? 0 : 1
        idx2   = !rat.include?("rating") ? 2 : 3

        date   = it.css('div.info li')[2].css('span')[idx1].text
        comment= it.css('div.info li')[3].css('span')[0].text if it.css('div.info li').size>idx2 and it.css('div.info li')[3]

        mdate2 = (mdate1.include?('(')) ? mdate1.split('(')[0] : mdate1

        # Get date from detail page
        if !mdate2.include?('-') and mdate2.size>4
            dpage = Nokogiri::HTML(open(link, "Accept" => "text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8",
                                       "Accept-Language" => "zh-TW,zh;q=0.8,en;q=0.6,en-US;q=0.4",
                                       "Connection" => "keep-alive",
                                       "User-Agent" => "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_9_2) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/34.0.1847.137 Safari/537.36"
                                      ))
            dpage.encoding = 'utf-8'
            mdate2 = dpage.css('span[@class="year"]').text[1..4]
        end

        mdate2 = "1000-01-01" if /^\D+/.match(mdate2.chomp)
        p "#{title} #{mdate2}"

        did    = /subject\/(\d+)\//.match(link)[1]    
        rating = rat[6].to_i
        dateutc= DateTime.strptime(date, '%Y-%m-%d').to_time.utc

        p "#{did} #{rating} #{dateutc} | #{title} | #{comment} | #{mdate3}"

        doc = { "id" => did.to_i,
                "title" => title,
                "imgsrc" => imgsrc,
                "link" => link,
                "rating" => rating,
                "date" => dateutc,
                "mdate" => mdate3,
                "comment" => comment
        }

        result = $coll.find("id" => did.to_i, :limit=>1 )
        if !result
            $coll.insert(doc)
        else 
            $coll.update({"id" => did.to_i}, doc)
        end
    end
end

$url="http://movie.douban.com/people/kalashnikov/wish"

page = Nokogiri::HTML(open($url, "Accept" => "text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8",
                           "Accept-Language" => "zh-TW,zh;q=0.8,en;q=0.6,en-US;q=0.4",
                           "Connection" => "keep-alive",
                           "User-Agent" => "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_9_2) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/34.0.1847.137 Safari/537.36"
                          ))
page.encoding = 'utf-8'

max = 0 
page.css('div.paginator a').each do |l|

    # Get the max number of movie list
    link = l['href']
    num  = /wish\?start=(\d+)&/.match(link)[1].to_i
    max  = num if num > max
end

# Parse first page
extractData(page)

(15..max).step(15).each do |i|
    link = "http://movie.douban.com/people/kalashnikov/wish?start=#{i}&amp;sort=time&amp;rating=all&amp;filter=all&amp;mode=grid"
    page = Nokogiri::HTML(open(link, "Accept" => "text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8",
                               "Accept-Language" => "zh-TW,zh;q=0.8,en;q=0.6,en-US;q=0.4",
                               "Connection" => "keep-alive",
                               "User-Agent" => "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_9_2) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/34.0.1847.137 Safari/537.36"
                              ))
    page.encoding = 'utf-8'
    extractData(page)
end

=begin
page.css('li.mdMN02Li').each do |o|

end

            imglink = "https://store.line.me" + o.css('a')[0]['href']     # Get detail webpage link

            dpage = Nokogiri::HTML(open(imglink, "Accept" => "text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8",
                                        "Accept-Language" => "zh-TW,zh;q=0.8,en;q=0.6,en-US;q=0.4",
                                        "Cookie" => newck,
                                        "Connection" => "keep-alive",
                                        "User-Agent" => "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_9_2) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/34.0.1847.137 Safari/537.36"
                                       ))
            dpage.encoding = 'utf-8'

            did       = imglink.split('=')[1]
            dtext     = dpage.css('p.mdMN07Desc')[0].text
            imgtext   = dpage.css('h2.mdMN05Ttl')[0].text
            imgsrc    = dpage.css('div.mdMN05Img img')[0]['src']
            detailImg = dpage.css('div.mdMN07Img img')[0]['src']

=end
