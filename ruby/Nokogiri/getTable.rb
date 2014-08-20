#!/usr/local/rvm/rubies/ruby-2.0.0-p247/bin/ruby

#
# Parse HTML Table using Nokogiri
#
# Use force_encoding for original coding
# then use UTF-8 for special character encoding
#
require 'nokogiri'
require 'open-uri'

# encoding: utf-8
Encoding.default_external = Encoding::UTF_8
Encoding.default_internal = Encoding::UTF_8

link = "http://homepage2.nifty.com/SHAKAI/JIDAI.HTM"
page = Nokogiri::HTML(open(link, "Accept" => "text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8",
                           "Connection" => "keep-alive",
                           "User-Agent" => "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_9_2) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/34.0.1847.137 Safari/537.36").read.force_encoding("Shift_JIS").encode('UTF-8', undef: :replace, replace: ''), nil, 'utf-8')

flag=false
page.css('table tbody tr').each do |o|

    year, event, key, msg = o.css('td')[0].text, o.css('td')[1].text, o.css('td')[2].text, o.css('td')[3].text

    # Replace space/newline with one
    key = key.gsub!(/\s+/,' ') if key=~/\s+/
    key = key.gsub!(/\r+/,' ')  if key=~/\r/
    key = key.gsub!(/\n+/,' ')  if key=~/\n/

    msg = msg.gsub!(/\s+/,' ') if msg=~/\s+/
    msg = msg.gsub!(/\r+/,' ')  if msg=~/\r/
    msg = msg.gsub!(/\n+/,' ')  if msg=~/\n/
    
    puts "|#{year}|#{event}|#{key}|#{msg}|"
    puts "|-------|--------|------|------|" if !flag
    flag = true if !flag
end
