#!/usr/local/rvm/rubies/ruby-2.0.0-p247/bin/ruby
require 'nokogiri'
require 'open-uri'
require 'openssl'
require 'mongo'

include Mongo

# Setting for MongoDB
$db = MongoClient.new("localhost", 27017).db("obmWeb")
$auth = $db.authenticate(ENV['MONGO_WEB_ACCOUNT'],ENV['MONGO_WEB_PASSWORD'])
$coll = $db["stickers"]

$coll.find({"id"=>{"$lt"=>1000000}}).sort( {id: -1 }).each do |f|
    imglink = f["thumbnail"]

    begin 
        open(imglink) {} 
    rescue 
        $coll.remove({"id"=>f["id"]})
        puts "Remove: #{f["id"]}"
    end
end

