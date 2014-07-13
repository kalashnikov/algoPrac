#!/usr/local/rvm/rubies/ruby-2.0.0-p247/bin/ruby

#
# This ruby script retrieve Theme data from LINE official site
# And save it into MongoDB
#

require 'rubygems'
require 'nokogiri'
require 'open-uri'
require 'openssl'
require 'mongo'
include Mongo

# Setting for MongoDB
$db = MongoClient.new("localhost", 27017).db("obmWeb")
$auth = $db.authenticate(account,passwd)
$coll = $db["themes"]

$priceTable=Hash.new
$priceTable[30]=25
$priceTable[60]=50
$priceTable[90]=75

cookie = open("https://store.line.me/stickershop/list?page=1&listType=top", :ssl_verify_mode => OpenSSL::SSL::VERIFY_NONE).meta['set-cookie']
                                          
newck  = "store_locale=zh_TW; store_lang=zh-hant; " + cookie

link = "https://store.line.me/themeshop/showcase/zh-Hant"
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

    return if !dpage.css('p.mdMN07Desc')[0]

    did       = imglink.split('/')[-2]
    dtext     = dpage.css('p.mdMN07Desc')[0].text
    dprice    = dpage.css('p.mdMN05Price')[0].text.gsub!(/￥/,"").to_i*0.3
    imgtext   = dpage.css('h2.mdMN05Ttl')[0].text
    imgsrc    = dpage.css('div.mdMN05Img img')[0]['src']

    # Preview Image of Theme
    detailImg = []
    dpage.css('li.mdMN07Li').each do |di|
        detailImg.push(di.css('img')[0]['src'].chomp)
    end

    begin
        open(imgsrc) {}
    rescue
        return
    end

    #                property :id,              String 
    #                property :name,            String
    #                property :tag,           [String]
    #                property :detail,          String
    #                property :description,     String
    #                property :thumbnail,       String
    #                property :detailImg,     [String]

                    puts "#{did} #{imgtext} #{imglink} #{dtext} #{imgsrc} #{dprice}"
    doc = { "id" => did,
            "sticker_id" => did,
            "name" => imgtext,
            "tag" => { },
            "detail" => imglink,
            "description" => dtext,
            #"price" => dprice.to_i,
            "price" => $priceTable[dprice.to_i],
            "thumbnail" => imgsrc,
            "weigth" => (1*2).to_i,
            "detailImg" => detailImg 
    }
    $coll.insert(doc)
=begin
    result = $coll.find("id" => did, :limit=>1 )
    if !result
        $coll.insert(doc)
    else 
        $coll.update({"id" => did}, doc)
    end
=end
end
