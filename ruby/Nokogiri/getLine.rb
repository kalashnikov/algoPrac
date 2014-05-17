#!/usr/local/rvm/rubies/ruby-2.0.0-p247/bin/ruby
require 'nokogiri'
require 'open-uri'
require 'openssl'

#
# This ruby script generate Sticker thumbnail from LINE official site
#

$OPNAME = ["official","creator"]
$OPLIST = ["https://store.line.me/stickershop/list?page=", 
           "https://store.line.me/stickershop/showcase/top_creators?page="]

cookie = open("https://store.line.me/stickershop/list?page=1&listType=top", :ssl_verify_mode => OpenSSL::SSL::VERIFY_NONE).meta['set-cookie']#.split('; ',2)[0]
                                          
newck  = "store_locale=zh_TW; store_lang=zh-hant; " + cookie

$OPLIST.each do |opl|
    str = $OPNAME[$OPLIST.index(opl)]
    File.open("#{str}.html",'w') do |output|

        (1..10).each do |n|

            link = "#{opl}#{n}&listType=top"
            page = Nokogiri::HTML(open(link, "Accept" => "text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8",
                                             "Accept-Language" => "zh-TW,zh;q=0.8,en;q=0.6,en-US;q=0.4",
                                             "Cookie" => newck,
                                             "Connection" => "keep-alive",
                                             "User-Agent" => "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_9_2) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/34.0.1847.137 Safari/537.36"
                                             ))
            page.encoding = 'utf-8'

            
            page.css('li.mdMN02Li').each do |o|
                output.puts '<div class="pin">'
                
                imglink = "https://store.line.me" + o.css('a')[0]['href']     # Get detail webpage link
                imgsrc  = o.css('div.mdMN02Img img')[0]['src']                # Get Image Src Link
                imgtext = o.css('div.mdMN02Desc')[0].text                     # Get Text

                dpage = Nokogiri::HTML(open(imglink, "Accept" => "text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8",
                                           "Accept-Language" => "zh-TW,zh;q=0.8,en;q=0.6,en-US;q=0.4",
                                           "Cookie" => newck,
                                           "Connection" => "keep-alive",
                                           "User-Agent" => "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_9_2) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/34.0.1847.137 Safari/537.36"
                                          ))
                dpage.encoding = 'utf-8'

                dtext = dpage.css('p.mdMN07Desc')[0].text

                output.puts "\t<a href=\"#{imglink}\">" 
                output.puts "\t\t<img src=\"#{imgsrc}\" />"
                output.puts "\t</a>" 
                output.puts "\t<p> <h3>#{imgtext}</h3><br> #{dtext} </p>" 

                output.puts '</div>'
            end
            output.puts
        end
    end
end
