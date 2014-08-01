#!/usr/local/rvm/rubies/ruby-2.0.0-p247/bin/ruby
require 'mongo'
#
# This script is to update Random field based description and time
#

# encoding=utf-8 

include Mongo

# Setting for MongoDB
$db = MongoClient.new("localhost", 27017).db("obmWeb")
$auth = $db.authenticate(ENV['MONGO_WEB_ACCOUNT'],ENV['MONGO_WEB_PASSWORD'])
$coll = $db["stickers"]

n = $coll.find({})

count = 0
n.each do |i|
    i["random"] = i["description"].hash * Time.now.hash % 100000000  
    i["update_at"] = Time.now.utc
    begin 
        $coll.update({"id" => i["id"]}, i, {:upsert=>true})
    rescue
        puts "ERROR: #{i["id"]}"
    end
end

puts %x[date]
