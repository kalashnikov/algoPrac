#!/usr/local/rvm/rubies/ruby-2.0.0-p247/bin/ruby
require 'wikipedia'

#
# This script use wikipedia-client API to get information for Timeline.js
# Ref.1 : https://github.com/kenpratt/wikipedia-client
# Ref.2 : http://timeline.knightlab.com/
#

Wikipedia.Configure {
    domain 'ja.wikipedia.org'
    path   'w/api.php'
}

if ARGV.length==0
    puts "Input keyword"
    exit
end

last = ""
File.open(ARGV[0]).each do |f|
    line  = f.chomp.gsub!(/『/,",").gsub!(/』/,",")#.gsub!(/\//,",")
    array = line.split(',')
    title = array[1]
    page = Wikipedia.find(title)

    imgDes  = ""
    imgName = ""

    next if !page.content
    page.content.split("\n").each do |l|
        next if l =~ /^{{/ # Note for wiki page
  
        # Get Image Name and Image Description
        if l =~ /^\[\[\S+:.*\]\]$/  # File
            imgName = /\[\[\S+:([^|]+)|/.match(l)[1]
            imgName = imgName.gsub!(/ /,"_") if imgName.include?(" ")
            imgDes  = l
            next
        end

        next if l.chomp.length==0
        abs = l
        abs = abs.gsub!(/\[\[/,"") if abs.include?("[[")
        abs = abs.gsub!(/\]\]/,"") if abs.include?("]]")
        abs = abs.gsub!(/'''/,"")  if abs.include?("'''")
        abs = abs.gsub!(/,/,"，")  if abs.include?(",")
        array.push("") if array.length==2
        array.push(abs)
        break
    end
    array[0] = array[0].gsub!(/年.*/,"") if array[0].include?("年")
    array[0].chomp.delete('　')=="" ? array[0] = last : last = array[0]
    last = array[0] if last==""
   
    # Search Image URL from imageUrl array by Name
    image = page.image_urls
    if image.length!=0
        imageUrl=""
        image.each do |f|
            if f.include?(imgName)
                imageUrl = f
            end
        end
        imageUrl = image.last if imageUrl==""
    end
    
    imgDes = imgDes.split('|').last if imgDes.include?("|")
    imgDes = imgDes.gsub!(/\[\[/,"") if imgDes.include?("[[")
    imgDes = imgDes.gsub!(/\]\]/,"") if imgDes.include?("]]")

    if imageUrl 
       imageUrl = "" if imageUrl.include?("BuddhaHead.jpg") or imageUrl.include?("Lit.jpg") or imageUrl.include?("Castle_in_Inuyama")
    end
    imageDes = imgName if imageUrl!="" and imgDes==""

    str = array[1..-1].join(',')
    puts "#{array[0]},#{title},#{imageUrl},#{imgDes},#{imgName},#{str}"
end


#p page.categories

#page.links

#page.extlinks

#p page.images
#p page.image_urls

