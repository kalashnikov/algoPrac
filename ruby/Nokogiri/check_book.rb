
require 'mongo'
include Mongo

# Setting for MongoDB
$db        = MongoClient.new("localhost",27017, :pool_size =>15).db("aozora")
$coll      = $db["books"]

# encoding: utf-8
Encoding.default_external = Encoding::UTF_8
Encoding.default_internal = Encoding::UTF_8

count = 0
$section = ""
$lastAuthor = ""
list = []
File.open("result_0515_all.csv").each_line do |l|
    next if l.include?("###")
    title = l.gsub(/（抄）/,"").gsub("　"," ").chomp.strip
    next if title==""

    ary = title.split(",")
    $section = ary[0].split(' ')[-1]
    $author  = ary[1].split(' ')[0]
    $title   = ary[1].split(' ')[1]

    d = $coll.find(:title => $title, :author => $author).first
    if d && d["author"].include?($author) 
        d["tag"] = d["tag"] ? d["tag"].push($section) : [ $section ]
        d["tag"].uniq!
        puts " #{$section} #{$author} | #{$title} | #{d["booklink"]}"
        count += 1
        $coll.update( {"id" => d["id"]}, d )
        list.push($title)
    end
end

puts "#############"
list.each do |l|
    d = $coll.find(:title => l).first
    puts "#{d["title"]}, #{d["author"]}, #{d["tag"]} => #{d["booklink"]}" if d 
end
puts "SIZE: #{list.size}"
