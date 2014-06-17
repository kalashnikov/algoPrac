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

    return if !dpage.css('p.mdMN07Desc')[0]

    did       = imglink.split('=')[1]
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
    #               puts imglink
    #               puts "#{did} #{imgtext} #{imglink} #{dtext} #{imgsrc} "

    doc = { "id" => did.to_i,
            "sticker_id" => did.to_i,
            "name" => imgtext,
            "tag" => { },
            "detail" => imglink,
            "description" => dtext,
            "price" => dprice.to_i,
            "thumbnail" => imgsrc,
            "weigth" => 1,
            "detailImg" => detailImg 
    }

    $coll.insert(doc)
    puts "=> Insert #{did} : #{imglink} ... "
end


idxSet=Set.new

count=0
limit=400
startIdx=0
$coll.find({"id"=>{"$lt"=>1000000}}).sort( {id: -1 }).each do |f|
    idxSet.add(f["id"].to_i)
    count+=1
    if count==20
        startIdx = f["id"]
        break
    end
end

endIdx=startIdx+limit
idxSet=Set.new((startIdx..endIdx).to_a)-idxSet

puts "### Start from #{startIdx} " 
puts "### Scan for Range: #{limit} " 

idxSet.each do |i|
    getLineByID(i)
end
