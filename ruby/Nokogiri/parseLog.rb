#!/usr/local/rvm/rubies/ruby-2.0.0-p247/bin/ruby
# encoding=utf-8 
require 'set'
require 'uri'
require 'mongo'

include Mongo

# Setting for MongoDB
$db = MongoClient.new("localhost", 27017).db("obmWeb")
$auth = $db.authenticate(ENV['MONGO_WEB_ACCOUNT'],ENV['MONGO_WEB_PASSWORD'])
$coll = $db["stickers"]


exit if ARGV.length==0

#STDOUT.set_encoding("Big5")
#puts STDOUT.internal_encoding
#puts STDOUT.external_encoding

word=""
target=""

worddb = Hash.new{|h,k| h[k]=Set.new}
wordcount=Hash.new{|h,k| h[k]=0}

count = 0
isFilter = false
File.open(ARGV[0]).each do |l|
    str = l.chomp.encode!('UTF-8', 'binary', invalid: :replace, undef: :replace, replace: '')
    /\"GET(.+) HTTP.*\"/.match(str) do |a|
        url = a[1]
        url = URI.unescape(a[1])
        if url.include?('-')        
            url = url.gsub!(/-/,'%') 
            url = URI.unescape(a[1])
        end
        next if url.chomp.length==0
        url = url.gsub!(/\+/,' ') if url.include?('+')
#        p "#{count} | #{url.chomp}"
        if url.include?("filter")
           word=url.split('=')[1]
           isFilter=true
        elsif word and isFilter and url.include?("detail")
           target=url.split('/')[2]
#           p "====> #{word} : #{target}"
           wordcount[word.force_encoding("UTF-8")]+=1
           worddb[word.force_encoding("UTF-8")].add(target)
           isFilter=false
        end
    end
    count+=1
end

puts
puts "### Summary ###"
puts 

File.open("search.csv",'w') do |file|
    wordcount.sort_by{|k,v| v}.reverse.each do |k,v|
        file.print "#{k}, #{v}, "
        puts "#{k}, #{v}"
        worddb[k].each do |n|
            itr = $coll.find({"id"=>n.to_i})
            next if !itr or itr.count()==0
            name = itr.first['name']
            file.print "#{name}(#{n}),"
        end
        file.print "\n"
    end
end

=begin
worddb.sort_by{|k,v| v.size}.reverse.each do |k,v|
    print "#{k} [#{v.size}]: "
    v.each do |n|
        print "#{n} "
    end
    print "\n"
end

wordSet.each do |w|
    puts "#{w} | #{w.encoding}"
end
=end
