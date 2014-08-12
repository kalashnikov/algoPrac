#!/usr/local/rvm/rubies/ruby-2.0.0-p247/bin/ruby
require 'nokogiri'
require 'open-uri'
require 'openssl'
#
# This script get Douban movie watch list and save into MongoDB
# 

$base= "http://tieba.baidu.com/"
$url = "http://tieba.baidu.com/f?kw=%CE%D2%D3%FB%B7%E2%CC%EC"

page = Nokogiri::HTML(open($url, "Accept" => "text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8",
                           "Accept-Language" => "zh-TW,zh;q=0.8,en;q=0.6,en-US;q=0.4",
                           "Connection" => "keep-alive",
                           "User-Agent" => "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_9_2) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/34.0.1847.137 Safari/537.36"
                          ))
page.encoding = 'utf-8'

max = 0
hash= Hash.new
page.css('div.threadlist_text').each do |it|
    next if !it.at_css('span')
    next if !it.at_css('span img')
    next if !it.css('span img')[0]['src'].include?("jing") and !it.css('span img')[0]['src'].include?("zding") 

    title  = it.css('a')[0]['title']
    next if title.include?("我欲封天吧") # skip fixed article

    if title =~ /第(\S+)章/
        num    = /第(\S+)章/.match(title)[1].to_i
    else 
        next  
    end
    link   = $base + it.css('a')[0]['href']
    #puts "#{title} | #{link} | #{num}"

    max = num if num > max 
    hash[num] = title + "|" + link
end

a = hash[max].split('|')
title = a[0]
link  = a[1]
contents = %x[python b.py #{link}].chomp.gsub(/<br \/>/,"")

p contents
