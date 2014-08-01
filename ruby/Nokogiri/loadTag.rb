#!/usr/local/rvm/rubies/ruby-2.0.0-p247/bin/ruby
#
# This script load sticker tags from CSV 
# And update in MongoDB
#

require './insertSticker.rb'

if ARGV.length!=1
    puts "Please provide Tag file."
    exit
end

# Load tags from file
tagHash = {}
tagSet  = Set.new
File.open(ARGV[0],'r:UTF-8').each do |l|
    r = l.chomp.split(',')
    next if r[0]=='ID'
    id, tag = r[0], r[1]
    tagHash[id.to_i]=tag.split('.')
    tag.split('.').each do |i|
        tagSet.add(i)
    end
end

# Check Database and Update 
needLoad = []
File.open('nonExist.csv','w') do |out|
    tagHash.each do |k,v|
        result = $coll.find_one("sticker_id" => k)
        if !result
            out.puts k
            needLoad.push(k)
        else
            result['tag'] = v
            $coll.update({"sticker_id" => k }, result, {:upsert=>true})
        end
    end
end

# Write out tag for cache 
File.open('/var/opt/www/sinatra/public/tagList','w') do |out|
    tagSet.each do |i|
        out.puts i
    end
end

needLoad.each do |id|
    puts "Checking #{id} ... "
    getLineByID(id)
end

puts %x[date]
