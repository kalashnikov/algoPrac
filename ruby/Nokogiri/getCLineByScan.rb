#!/usr/local/rvm/rubies/ruby-2.0.0-p247/bin/ruby
require 'nokogiri'
require 'open-uri'
require 'openssl'
require 'mongo'
require 'set'

include Mongo

# Setting for MongoDB
$db = MongoClient.new("localhost", 27017).db("obmWeb")
$auth = $db.authenticate(ENV['MONGO_WEB_ACCOUNT'],ENV['MONGO_WEB_PASSWORD'])
$coll = $db["stickers"]

$priceTable=Hash.new
$priceTable[30]=25
$priceTable[60]=50
$priceTable[90]=75

# This function get Sticker information from Official Site by ID 
def getLineByID(id)

    # Get cookie
    cookie = open("https://store.line.me/stickershop/list?page=1&listType=top", :ssl_verify_mode => OpenSSL::SSL::VERIFY_NONE).meta['set-cookie']
    newck  = "store_locale=zh_TW; store_lang=zh-hant; " + cookie
    
    imglink = "https://store.line.me/stickershop/detail?packageId=#{id}"     # Detail webpage link
    dpage = Nokogiri::HTML(open(imglink, "Accept" => "text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8",
                                "Accept-Language" => "zh-TW,zh;q=0.8,en;q=0.6,en-US;q=0.4",
                                "Cookie" => newck,
                                "Connection" => "keep-alive",
                                "User-Agent" => "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_9_2) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/34.0.1847.137 Safari/537.36"
                               ))
    dpage.encoding = 'utf-8'

    # Next if Official Site do not have this sticker
    return if !dpage.css('p.mdMN07Desc')[0]

    did       = imglink.split('=')[1]
    dtext     = dpage.css('p.mdMN07Desc')[0].text
    dprice    = dpage.css('p.mdMN05Price')[0].text.gsub!(/￥/,"").to_i*0.3
    imgtext   = dpage.css('h2.mdMN05Ttl')[0].text
    imgsrc    = dpage.css('div.mdMN05Img img')[0]['src']
    detailImg = dpage.css('div.mdMN07Img img')[0]['src']

    # Check Img Src Link 
    begin
        open(imgsrc) {}
    rescue
        return  
    end

    #                property :id,             Integer
    #                property :name,            String
    #                property :tag,           [String]
    #                property :detail,          String
    #                property :description,     String
    #                property :thumbnail,       String
    #                property :detailImg,       String
    #               puts imglink
    #               puts "#{did} #{imgtext} #{imglink} #{dtext} #{imgsrc} "

    doc = { "id" => did.to_i,
            "sticker_id" => did.to_i,
            "name" => imgtext,
            "tag" => { },
            "detail" => imglink,
            "description" => dtext,
            "price" => $priceTable[dprice.to_i],
            "thumbnail" => imgsrc,
            "weigth" => 1,
            "detailImg" => detailImg 
    }

    puts "=> Insert #{did} : #{imglink} ... "
    $coll.insert(doc)
    #result = $coll.find("id" => did.to_i, :limit=>1 )
    #if !result
    #    $coll.insert(doc)
    #    puts "=> Insert #{did} : #{imglink} ... "
    #else
    #    $coll.update({"id" => did.to_i}, doc)
    #end

#    $coll.insert(doc)
#    puts "=> Insert #{did} : #{imglink} ... "
end


scanAll = true
idxSet=Set.new

count=0
limit=6000
startIdx=0
$coll.find({"id"=>{"$gt"=>1000000}}).sort( {id: -1 }).each do |f|
    idxSet.add(f["id"].to_i)
    if !scanAll and count<100 
        count+=1
        startIdx = f["id"]
    end
end

startIdx=1000000
endIdx=startIdx+limit
idxSet=Set.new((startIdx..endIdx).to_a)-idxSet

p idxSet.size

puts "### Start from #{startIdx} " 
puts "### Scan for Range: #{limit} " 

=begin
idxSet.each do |i|
    getLineByID(i)
end
=end
