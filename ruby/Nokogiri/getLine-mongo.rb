#!/usr/local/rvm/rubies/ruby-2.0.0-p247/bin/ruby

#
# This ruby script retrieve Sticker data from LINE official site
# And save it into MongoDB
#
# http://api.mongodb.org/ruby/current/Mongo/Collection.html#find-instance_method
# http://api.mongodb.org/ruby/1.10.1/Mongo/Collection.html#find_and_modify-instance_method
# https://github.com/mongodb/mongo-ruby-driver/wiki/FAQ
# https://github.com/mongodb/mongo-ruby-driver
#

require 'rubygems'
require 'nokogiri'
require 'open-uri'
require 'openssl'
require 'mongo'
include Mongo

# Setting for MongoDB
$db = MongoClient.new("localhost", 27017).db("obmWeb")
$auth = $db.authenticate("obm", "back54321")
$coll = $db["stickers"]

$priceTable=Hash.new
$priceTable[30]=25
$priceTable[60]=50
$priceTable[90]=75

#
$OPNAME = ["official","creator"]
#$OPLIST = ["https://store.line.me/stickershop/list?page=",
#           "https://store.line.me/stickershop/showcase/top_creators?page="]

$OPLIST = ["https://store.line.me/stickershop/showcase/top/zh-Hant?page=",
           "https://store.line.me/stickershop/showcase/top_creators/zh-Hant?page="]

#cookie = open("https://store.line.me/stickershop/list?page=1&listType=top", :ssl_verify_mode => OpenSSL::SSL::VERIFY_NONE).meta['set-cookie']
cookie = open("https://store.line.me/stickershop/showcase/top/zh-Hant?page=1", :ssl_verify_mode => OpenSSL::SSL::VERIFY_NONE).meta['set-cookie']
                                          
newck  = "store_locale=zh_TW; store_lang=zh-hant; " + cookie

$OPLIST.each do |opl|
    str = $OPNAME[$OPLIST.index(opl)]
    #(1..30).each do |n|
    (1..2).each do |n|
        link = "#{opl}#{n}"
        page = Nokogiri::HTML(open(link, "Accept" => "text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8",
                                   "Accept-Language" => "zh-TW,zh;q=0.8,en;q=0.6,en-US;q=0.4",
                                   "Cookie" => newck,
                                   "Connection" => "keep-alive",
                                   "User-Agent" => "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_9_2) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/34.0.1847.137 Safari/537.36"
                                  ))
        page.encoding = 'utf-8'

        page.css('li.mdMN02Li').each do |o|

            imglink = "https://store.line.me" + o.css('a')[0]['href']     # Get detail webpage link

            dpage = Nokogiri::HTML(open(imglink, "Accept" => "text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8",
                                        "Accept-Language" => "zh-TW,zh;q=0.8,en;q=0.6,en-US;q=0.4",
                                        "Cookie" => newck,
                                        "Connection" => "keep-alive",
                                        "User-Agent" => "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_9_2) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/34.0.1847.137 Safari/537.36"
                                       ))
            dpage.encoding = 'utf-8'

            #did       = imglink.split('=')[1]
            did       = imglink.split('/')[-2]
            dtext     = dpage.css('p.mdMN07Desc')[0].text
            dprice    = dpage.css('p.mdMN05Price')[0].text.gsub!(/￥/,"").to_i*0.3
            imgtext   = dpage.css('h2.mdMN05Ttl')[0].text
            imgsrc    = dpage.css('div.mdMN05Img img')[0]['src']
            detailImg = dpage.css('div.mdMN07Img img')[0]['src']

            #                property :id,             Integer
            #                property :name,            String
            #                property :tag,           [String]
            #                property :detail,          String
            #                property :description,     String
            #                property :thumbnail,       String
            #                property :detailImg,       String

                            puts "#{did} #{imgtext} #{imglink} #{dtext} #{imgsrc} "
=begin
            doc = { "id" => did.to_i,
                    "sticker_id" => did.to_i,
                    "name" => imgtext,
                    "tag" => { },
                    "detail" => imglink,
                    "description" => dtext,
                    #"price" => dprice.to_i,
                    "price" => $priceTable[dprice.to_i],
                    "thumbnail" => imgsrc,
                    "weigth" => (n*2).to_i,
                    "detailImg" => detailImg 
            }

            result = $coll.find("id" => did.to_i, :limit=>1 )
            if !result
                $coll.insert(doc)
            else 
                $coll.update({"id" => did.to_i}, doc)
            end
=end
        end
    end
end
