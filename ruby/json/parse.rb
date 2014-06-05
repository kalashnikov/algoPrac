#!/Users/kalaexj/.rvm/rubies/ruby-2.1.1/bin/ruby
require 'json'
require 'set'

s = Set.new
c = Set.new
outputs = Array.new 

File.open("output.json","w") do |out|
    File.open(ARGV[0]).each do |l|
        array= []
        data = JSON.parse(l)
        data["data"]["posts"].each_with_index do |po,i|
            if s.include?(po["slug"])
                po["slug"] = po["slug"]+"1"
                c.add(i)
            end
            s.add(po["slug"])
        end
        data["data"]["tags"].each_with_index do |po,i|
            next if !c.include?(i)
            po["slug"] = po["slug"]+"1"
        end
#        array.reverse.each do |i|
#            data["data"]["posts"].delete_at(i)
#            puts "### Delete: #{i}"
#        end
#        ts = data["data"]["tags"].size
#        ps = data["data"]["posts_tags"].size
#        puts "#{ts} #{ps}"
        out.puts data.to_json
    end
end

p s.size
