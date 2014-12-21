
require 'set'

ans= 0
t1 = Time.now.to_f

#============================================================================#
#============================================================================#
#============================================================================#

# Euler8
#data="7316717653133062491922511967442657474235534919493496983520312774506326239578318016984801869478851843858615607891129494954595017379583319528532088055111254069874715852386305071569329096329522744304355766896648950445244523161731856403098711121722383113622298934233803081353362766142828064444866452387493035890729629049156044077239071381051585930796086670172427121883998797908792274921901699720888093776657273330010533678812202354218097512545405947522435258490771167055601360483958644670632441572215539753697817977846174064955149290862569321978468622482839722413756570560574902614079729686524145351004748216637048440319989000889524345065854122758866688116427171479924442928230863465674813919123162824586178664583591245665294765456828489128831426076900422421902267105562632111110937054421750694165896040807198403850962455444362981230987879927244284909188845801561660979191338754992005240636899125607176060588611646710940507754100225698315520005593572972571636269561882670428252483600823257530420752963450"
#
#t1 = Time.now.to_f
#
#N   = 13
#len = data.length-N
#max = 0 
#(0..len).each do |i|
#    val = 1
#    (0..N-1).each do |n|
#        val *= data[i+n].to_i
#    end
#    max = val if val > max
#end
#puts max 

#============================================================================#
#============================================================================#
#============================================================================#

# Euler9
#(1..997).each do |n1|
#    (n1+1..998).each do |n2|
#        if n1*n1+n2*n2-(1000-n1-n2)*(1000-n1-n2)==0
#            n3  = 1000-n1-n2
#            ans = n1*n2*n3
#            puts "#{n1}*#{n2}*#{n3}=#{ans}"
#            break
#        end
#    end
#end

#============================================================================#
#============================================================================#
#============================================================================#

# Prime helper library for Project Euler
# By TieSoul
#
# Implements the Sieve of Eratosthenes.
# Takes argument n and returns all primes up to n.
def sieve(n)
  # Array containing 0 through the max number
  s = (0..n).to_a
  # Set 0 and 1, nonprimes, to nil.
  s[0] = s[1] = nil
  s.each do |p|
    next unless p
    return s.compact if p * p > n
    # Set all values divisible by p that are above p squared to nil
    (p*p).step(n, p) { |m| s[m] = nil }
  end
  # Return the array without nil values
  s.compact
end
#
#def nth_prime(n)
#  sieve([20*n, 2000000].min)[n-1]
#end
#
#def sum_prime(n)
#  sieve(20000000).keep_if{|v| v<n}.inject{|sum,x| sum+x}
#end

#ans = sum_prime(2000000)

#============================================================================#
#============================================================================#
#============================================================================#

# Euler 11
#data=[[ 8, 02, 22, 97, 38, 15, 00, 40, 00, 75, 04, 05, 07, 78, 52, 12, 50, 77, 91,  8],
#      [49, 49, 99, 40, 17, 81, 18, 57, 60, 87, 17, 40, 98, 43, 69, 48, 04, 56, 62, 00],
#      [81, 49, 31, 73, 55, 79, 14, 29, 93, 71, 40, 67, 53, 88, 30, 03, 49, 13, 36, 65],
#      [52, 70, 95, 23, 04, 60, 11, 42, 69, 24, 68, 56, 01, 32, 56, 71, 37, 02, 36, 91],
#      [22, 31, 16, 71, 51, 67, 63, 89, 41, 92, 36, 54, 22, 40, 40, 28, 66, 33, 13, 80],
#      [24, 47, 32, 60, 99, 03, 45, 02, 44, 75, 33, 53, 78, 36, 84, 20, 35, 17, 12, 50],
#      [32, 98, 81, 28, 64, 23, 67, 10, 26, 38, 40, 67, 59, 54, 70, 66, 18, 38, 64, 70],
#      [67, 26, 20, 68, 02, 62, 12, 20, 95, 63, 94, 39, 63,  8, 40, 91, 66, 49, 94, 21],
#      [24, 55, 58, 05, 66, 73, 99, 26, 97, 17, 78, 78, 96, 83, 14, 88, 34, 89, 63, 72],
#      [21, 36, 23,  9, 75, 00, 76, 44, 20, 45, 35, 14, 00, 61, 33, 97, 34, 31, 33, 95],
#      [78, 17, 53, 28, 22, 75, 31, 67, 15, 94, 03, 80, 04, 62, 16, 14,  9, 53, 56, 92],
#      [16, 39, 05, 42, 96, 35, 31, 47, 55, 58, 88, 24, 00, 17, 54, 24, 36, 29, 85, 57],
#      [86, 56, 00, 48, 35, 71, 89, 07, 05, 44, 44, 37, 44, 60, 21, 58, 51, 54, 17, 58],
#      [19, 80, 81, 68, 05, 94, 47, 69, 28, 73, 92, 13, 86, 52, 17, 77, 04, 89, 55, 40],
#      [04, 52,  8, 83, 97, 35, 99, 16, 07, 97, 57, 32, 16, 26, 26, 79, 33, 27, 98, 66],
#      [88, 36, 68, 87, 57, 62, 20, 72, 03, 46, 33, 67, 46, 55, 12, 32, 63, 93, 53, 69],
#      [04, 42, 16, 73, 38, 25, 39, 11, 24, 94, 72, 18,  8, 46, 29, 32, 40, 62, 76, 36],
#      [20, 69, 36, 41, 72, 30, 23, 88, 34, 62, 99, 69, 82, 67, 59, 85, 74, 04, 36, 16],
#      [20, 73, 35, 29, 78, 31, 90, 01, 74, 31, 49, 71, 48, 86, 81, 16, 23, 57, 05, 54],
#      [01, 70, 54, 71, 83, 51, 54, 69, 16, 92, 33, 48, 61, 43, 52, 01, 89, 19, 67, 48]]
#
#ans = 0
#(0..19).each do |r|
#    (0..19).each do |c|
#        pro1 = pro2 = pro3 = pro4 = 0
#        pro1 = data[r][c]*data[r+1][c]*data[r+2][c]*data[r+3][c] if (r+3)<20
#        pro2 = data[r][c]*data[r][c+1]*data[r][c+2]*data[r][c+3] if (c+3)<20
#        pro3 = data[r][c]*data[r+1][c+1]*data[r+2][c+2]*data[r+3][c+3] if (c+3)<20 and (r+3)<20
#        pro4 = data[r][c]*data[r-1][c+1]*data[r-2][c+2]*data[r-3][c+3] if (c+3)<20 and (r+3)>=0
#        ans  = [ans,pro1,pro2,pro3,pro4].max
#    end
#end

#============================================================================#
#============================================================================#
#============================================================================#


# Euler12
=begin
require 'prime'
last = 0 
(1_000_000..100_000_000).each do |n|
    all = 1
    n.prime_division.each do |k,v|
        all *= (v+1)
    end
    if all + last > 500 
        puts "#{n}*#{n-1}"
        break 
    end
    last = all
end
=end


#============================================================================#
#============================================================================#
#============================================================================#

# Euler13 

#data = [3710728753390.210279879799822083,
#4637693767749.000971264812489697,
#7432498619952.474105947423330951,
#9194221336357.416157252243056330,
#2306758820753.934617117198031042,
#8926167069662.363382013637841838,
#2811287981284.997940806548193159,
#4427422891743.252032192358942287,
#4745144573600.130643909116721685,
#7038648610584.302543993961982891,
#6217645714185.656062950215722319,
#6490635246274.190492910143244581,
#9257586771833.721766196375159057,
#5820356532535.939900840263356894,
#8018119938482.628201427819413994,
#3539866437282.711265382998724078,
#8651550600629.586486153207527337,
#7169388870771.546649911559348760,
#5437007057682.668462462149565007,
#5328265410875.682844319119063469,
#3612327252500.029607107508256381,
#4587657617241.097644733911060721,
#1742370690585.186066044820762120,
#8114266041808.683061932846081119,
#5193432545172.838864191804704929,
#6246722164843.507620172791803994,
#1573244438690.812579451408905770,
#5503768752567.877309186254074496,
#1833638482533.015468619612434876,
#8038628759287.849020152168555482,
#7818283375799.310361474035685644,
#1672632010043.689784255353992093,
#4840309812907.779179908821879532,
#8708698755139.271185451707854416,
#5995940689575.653678210707492696,
#6979395067965.269474259770973916,
#4105268470829.908521139942736573,
#6537860736150.108085700914993951,
#3582903531743.471732693212357815,
#9495375976510.530594696606768315,
#8890280257173.322961917666871381,
#2526768027607.800301367868099252,
#3627021854049.770558562994658063,
#2407448690823.117497779236546625,
#9143028819710.328859780666976089,
#3441306557801.612781592181500556,
#2305308117281.643048762379196984,
#1148769693215.490281042402013833,
#6378329949063.625966649858761822,
#6772018697169.854431241957240991,
#9554825530026.352078153229679624,
#7608532713228.572311042480345612,
#3777424253541.129168427686553892,
#2370191327572.567528565324825826,
#2979886027225.833191312637514734,
#1849570145487.928898485682772607,
#3829820378303.147352772158034814,
#3482954382919.991818027891652243,
#4095795306640.523263253804410005,
#2974615218550.237130764225512118,
#4169811622207.297718615823667842,
#6246795719440.126904387710727504,
#2318970677254.791506150550495392,
#8618808822587.531452958409925120,
#1130673970830.472448381653387350,
#8295917476714.036319800818712901,
#9762333104481.838626951545633492,
#4284628018351.707052783183942588,
#5512160354698.120058176216521282,
#3223819573432.933994643750190783,
#7550616496518.477518073816883786,
#6217784275219.262340194239963916,
#3292418570714.734956691667468763,
#9951867143023.521962889489010242,
#7326746080059.154747183079839286,
#7684182252467.441716151403642798,
#9714261791034.259864720451689398,
#8778364618279.934631376775430780,
#1084880252167.467088321512018588,
#7132961247478.246453863699300904,
#6218407357239.979422340623539380,
#6662789198148.808779794187687614,
#6066182629368.283676474477923918,
#8578694408955.299065364044742557,
#6602439640990.538960712019821997,
#6491398268003.297315603712004137,
#1673093931987.275027546890690370,
#9480937724504.879515095410092164,
#7863916702118.749243199570064191,
#1536871371193.661495281130587638,
#4078992311553.556256114232242325,
#4488991150144.064802036906806396,
#4150312888033.953605329934036800,
#8123488067321.014673905856855793,
#8261657077394.832759223284594170,
#2291880205877.731971983945018088,
#7715854250201.654509041324580978,
#7210783843506.918615543566288406,
#2084960398013.400172393067166682,
#5350353422647.252425087405407559]
#
#ans = data.inject{|s,v|s+v}


#============================================================================#
#============================================================================#
#============================================================================#

# Euler16
#puts (2**100000).to_s.split('').inject(0){|s,v| s.to_i+v.to_i} 

#============================================================================#
#============================================================================#
#============================================================================#

# Euler17

#def getNum(n)
#    
#    numdb = { "1" => 3, "2" => 3, "3" => 5, "4" => 4, "5" => 4,
#              "6" => 3, "7" => 5, "8" => 5, "9" => 4, "10"=> 3,
#              "11"=> 6, "12"=> 6, "13"=> 8, "14"=> 8, "15"=> 7,
#              "16"=> 7, "17"=> 9, "18"=> 8, "19"=> 8, "20"=> 6,
#              "30"=> 6, "40"=> 5, "50"=> 5, "60"=> 5, "70"=> 7,
#              "80"=> 6, "90"=> 6,"100"=> 7,"1000"=>8
#    }
#
#    num = 0
#    if n==1000 
#        num = 3 + 8
#    elsif n/100!=0
#        num += numdb[(n/100).to_s].to_i + 7
#        num += getNum(n%100) + 3 if n%100!=0 # 3: and
#    elsif numdb.include?(n.to_s)
#        num += numdb[n.to_s].to_i
#    elsif n/10!=0 
#        num += numdb[(n%10).to_s].to_i + numdb[((n/10)*10).to_s].to_i
#    else 
#        puts "ASSERT #{n}"
#    end
#    return num
#end
#
#puts getNum(1)+getNum(2)+getNum(3)+getNum(4)+getNum(5)
#puts getNum(115)
#puts getNum(342)
#
#ans = 0
#(1..1000).each do |n|
#    ans += getNum(n)
#end

#============================================================================#
#============================================================================#
#============================================================================#

# Euler18
#max = [] 
#File.open("tri.txt").each do |l|
#File.open("p067_triangle.txt").each do |l|
#    lvl = l.chomp.split(' ').map{|v| v.to_i}
#    if max.empty?
#        max.push(lvl[0])
#    else
#        tmp = []
#        lvl.each_with_index do |v,i|
#            total = v
#            total += max[i]   if max[i] 
#            total = v + max[i-1] if max[i-1] and v+max[i-1]>total 
#            tmp.push(total)
#        end
#        max = tmp
#    end
#end
#puts max.max

#============================================================================#
#============================================================================#
#============================================================================#

# Euler19
# 1 Jan 1900 was a Monday.
# Thirty days has September,
# April, June and November.
# All the rest have thirty-one,
# Saving February alone,
# Which has twenty-eight, rain or shine.
# And on leap years, twenty-nine.
# A leap year occurs on any year evenly divisible by 4, but not on a century unless it is divisible by 400.
#
# How many Sundays fell on the first of the month during the twentieth century (1 Jan 1901 to 31 Dec 2000)?
#

#num = [31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]
#
#def leap(n)
#    leap = 0
#    leap = 1 if n%400==0 
#    leap = 1 if n%4==0 and n%100!=0
#    return leap.to_i
#end
#
#cur   = 0
#total = 0
#first = 0 
#(1900..2000).each do |n|
#    num.each do |m|
#        cur   = cur + m
#        cur   += 1 if m==28 and leap(n)
#        cur   %= 7
#        total += 1 if cur==0
#    end
#    first = total if n==1900 
#end
#ans = total-first

#============================================================================#
#============================================================================#
#============================================================================#

# Euler20 
#puts (1..100).inject(:*).to_s.split('').inject(0){|s,v| s+v.to_i}

#============================================================================#
#============================================================================#
#============================================================================#

# Euler21 
#def d(n)
#    (2..n/2).find_all{|v| n%v==0}.inject(1){|s,v| s+v}
#end
#
#list = Set.new 
#(1..10000).each do |n|
#    next if list.include?(n)
#    a = d(n)
#    next if a==n
#    if n==d(a)
#        list.add(a)
#        list.add(n)
#    end
#end
#puts list.inject(0){|s,v| s+v}

#============================================================================#
#============================================================================#
#============================================================================#

# Euler22
#aval    = Hash.new
#valList = Hash.new
#("A".."Z").each_with_index do |k,v|
#    aval[k] = v+1
#end
#
#data = []
#File.open("p022_names.txt").each do |l|
#    data += l.chomp.gsub!(/"/,"").split(",")
#end
#
#data.each do |c|
#    val  = c.to_s.split("").inject(0){|s,v| s+aval[v]}
#    valList[c]=val 
#end
#
#ans = 0
#data.sort_by!{|v| v }
#data.each_with_index do |k,v|
#    ans += (v+1)*valList[k] 
#end

#============================================================================#
#============================================================================#
#============================================================================#

# Euler23
#def d(n)
#    (2..n/2).find_all{|v| n%v==0}.inject(1){|s,v| s+v}
#end
#
#alist = (12..28123).find_all{|v| d(v)>v}
#aset  = Set.new(alist)
#
#nlist = []
#(1..28123).each do |v|
#    flag = true
#    alist.each do |n|
#        break if n > v  
#        if aset.include?(v-n)
#            flag = false
#            break
#        end
#    end
#    if flag 
#        nlist.push(v)
#    end
#end
#
#ans = nlist.inject(0){|s,v| s+v}

#============================================================================#
#============================================================================#
#============================================================================#

# Euler24


#(0..9).to_a.permutation.each_with_index do |v,i|
##    puts "#{i}: #{v}"
#    if i==1_000_000-1
#        ans = v.join 
#    end
#end


#============================================================================#
#============================================================================#
#============================================================================#

# Euler25
#def fib(n)
#    puts n if n<3
#    ans, f1, f2, n = 0, 1, 1, n-2 
#    while n!=0 
#        ans = f1 + f2
#        f1, f2, n = f2, ans, n-1
#    end
#    ans 
#end
#
#(100..1000000).each do |n|
#    if fib(n).to_s.length==1000 
#        ans = n 
#        break
#    end
#end

#============================================================================#
#============================================================================#
#============================================================================#

# Euler26 
#(1..1000).each do |n|
#    str   = ""
#    count = 0
#    nem   = 1
#    tab   = Hash.new
#    while true
#
#        base= nem*10
#        res = base % n
#        dem = (base/n).to_s
#        
#        if res==0
#            #puts "### #{n}: 0.#{str}" + dem + "\n"
#            break
#        end
#
#        key = "#{nem},#{dem}"
#        str += dem 
#        if tab.include?(key)
#            if count-tab[key]>ans+1
#                ans = count-tab[key]+1
#                #puts "### #{n}: 0.#{str}"
#            end
#            break
#        else
#            tab[key]=count
#            nem = res
#            count+=1
#        end
#    end
#end

#============================================================================#
#============================================================================#
#============================================================================#

# Euler27
#prime = Set.new(sieve(2000))
#p1000 = Set.new(sieve(1000))
#max = 0 
#p1000.each do |b|
#    (-1000..1000).each do |a|
#        (0..100).each do |n|
#            if !prime.include?(n*n+a*n+b)
#                if n>max
#                    max = n
#                    ans = a*b
#                end
#                break
#            end
#        end
#    end
#end

#============================================================================#
#============================================================================#
#============================================================================#

# Euler28
#ans = 1
#(1..500).each do |a|
#    n    = 2*a+1
#    ans += 4*(n*n) -6*(n-1)
#end

#============================================================================#
#============================================================================#
#============================================================================#

# Euler29
#all = Set.new
#(2..100).each do |a|
#    (a..100).each do |b|
#        all.add(a**b)
#        all.add(b**a)
#    end
#end
#ans = all.size

#============================================================================#
#============================================================================#
#============================================================================#

# Euler30
#ans = (100..1000000).to_a.keep_if{|n| n.to_s.split(//).inject(0){|s,i| s+(i.to_i**5)}==n}.inject(0){|s,i|s+i}

#============================================================================#
#============================================================================#
#============================================================================#

# Euler31
#list = [1,2,5,10,20,50,100]
#
#ans = 1 
#(0..2).each do |a|
#    if a*100 == 200
#        ans+=1 
#        break
#    end
#    (0..4).each do |b|
#        if a*100+b*50 == 200 
#            ans+=1 
#            break
#        end
#        break if a*100+b*50 > 200 
#        (0..10).each do |c|
#            if a*100+b*50+c*20 == 200 
#                ans+=1 
#                break
#            end
#            break if a*100+b*50+c*20 > 200 
#            (0..20).each do |d|
#                if a*100+b*50+c*20+d*10 == 200 
#                    ans+=1 
#                    break
#                end
#                break if a*100+b*50+c*20+d*10 > 200 
#                (0..40).each do |e|
#                    if a*100+b*50+c*20+d*10+e*5 == 200 
#                        ans+=1 
#                        break
#                    end
#                    break if a*100+b*50+c*20+d*10+e*5 > 200 
#                    (0..100).each do |f|
#                        break if a*100+b*50+c*20+d*10+e*5+f*2 > 200 
#                        g = 200 - (a*100+b*50+c*20+d*10+e*5+f*2)
#                        ans+=1 
#                    end
#                end
#            end
#        end
#    end
#end


#============================================================================#
#============================================================================#
#============================================================================#

# Euler33

#num = 1
#dem = 1
#(1..9).each do |b|
#    (1..9).each do |a|
#        next if a==b 
#            (1..9).each do |c|
#            next if c==a or c==b
#            if ((a*10+b)/(b*10+c).to_f)==(a/c.to_f)
#                puts "#{a}#{b}/#{b}#{c}"
#                num *= a
#                dem *= c
#            end
#        end
#    end
#end
#puts "#{num}/#{dem}"

#============================================================================#
#============================================================================#
#============================================================================#

# Euler34

def fac(n)
    (1..n).reduce(1,:*)
end

#def fac(n)
#    case n
#    when 0
#        return 1
#    when 3
#        return 6 
#    when 4 
#        return 24
#    when 5
#        return 120
#    when 6 
#        return 720 
#    when 7 
#        return 5040
#    when 8 
#        return 40320
#    when 9
#        return 362880
#    else
#        return n
#    end
#end
#
#def dfac(n)
#    return n.to_s.split(//).inject(0){|s,x| s+fac(x.to_i)}
#end
#
#def maxFac(n)
#    (4..9).each do |i|
#        return (0..i-1).to_a if fac(i)>(10**n)
#    end
#    return (0..9).to_a
#end
#
#def checkFreq(a,b)
#    return false if !(a-b).empty?
#    ah = Hash.new
#    bh = Hash.new
#    a.uniq.map{|i| ah[i]=0}
#    b.uniq.map{|i| bh[i]=0}
#    a.map{|i| ah[i]+=1}
#    b.map{|i| bh[i]+=1}
#    ah.each do |k,v|
#        return false if bh[k]!=v
#    end
#    return true
#end
#
#def checkSumDig(p)
#    tmp = [] 
#    facArr = maxFac(p)
#    #puts "#{p} | #{facArr.join}"
#    com    = facArr.repeated_combination(p).to_a
#    com.each do |n| 
#        nn   = n.join.to_i
#        sum  = n.inject(0){|s,i| s+fac(i)}
#        suma = sum.to_s.split(//).map{|x| x.to_i}
#        if checkFreq(n,suma) and nn>2
#            tmp.push(sum)
#            puts "#{n.join} (#{n.size}) | #{sum} (#{suma.size}) | #{n-suma}"
#            puts nn
#        end
#    end
#    return tmp
#end
#
#ans = [] 
#(1..7).each do |n|
#    ans += checkSumDig(n)
#end
#ans = ans.inject(0){|s,x| s+x}

#============================================================================#
#============================================================================#
#============================================================================#

# Euler35

#def cir(n)
#    all = [n.to_i]
#    arr = n.to_s.split(//)
#    len = arr.length
#    (1..len-1).each do |i|
#        all.push(arr.rotate(i).join.to_i)
#    end
#    return all
#end

#MAX = 1_000_000
#ans  = 0 
#prime = sieve(MAX)
#pSet = Set.new(prime)
#prime.each do |n|
#    next if !pSet.include?(n)
#    all = cir(n).uniq
#    if all.size==all.delete_if{|x| !pSet.include?(x)}.size
#        ans+=all.size
#    end
#    pSet -= all
#end

#============================================================================#
#============================================================================#
#============================================================================#

# Euler36
#def pal_s(s)
#    s.to_s == s.to_s.reverse
#end
#
#ans = 0 
#(1..1_000_000).each do |n|
#    next if !pal_s(n) or !pal_s(n.to_s(2))
#    ans += n
#end

#============================================================================#
#============================================================================#
#============================================================================#

# Euler 42
#list = Set.new 
#(1..100).each do |d|
#    num = (d)*(d+1)/2
#    list.add(num)
#end
#
#table = Hash.new
#('A'..'Z').each_with_index do |i,d|
#    table[i] = d+1 
#end
#
#data = []
#File.open("p042_words.txt").each do |l|
#    data += l.chomp.gsub!(/"/,"").split(",")
#end
#
#data.each do |w|
#    t = w.to_s.split(//).inject(0){|s,x| s+table[x]}
#    #puts "#{w}, #{t}"
#    ans += 1 if list.include?(t) 
#end

#============================================================================#
#============================================================================#
#============================================================================#

# Euler81
#SIZE=80
#cnt = 0
#array = Array.new{|h,a| h[a]=Array.new}
#File.open("p081_matrix.txt").each do |l|
#    array[cnt] = l.chomp.split(",").collect{|x| x.to_i}
#    cnt+=1
#end
#
#(0..SIZE-1).each do |r|
#    (0..SIZE-1).each do |c|
#        l = r>0 ? array[r-1][c] : 1_000_000
#        t = c>0 ? array[r][c-1] : 1_000_000
#        if l==1_000_000 and t==1_000_000 
#            l = 0
#            t = 0
#        end
#        array[r][c] += l<t ? l : t  
#    end
#end
#
#ans = array[SIZE-1][SIZE-1]

#============================================================================#
#============================================================================#
#============================================================================#
puts "Project Euler problem x: Answer #{ans} found in #{((Time.now.to_f - t1) * 1000).round 3} ms."
