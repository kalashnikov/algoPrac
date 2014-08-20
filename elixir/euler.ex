
defmodule Fib do
  def fib(0), do: 0
  def fib(1), do: 1
  def fib(n), do: fib(n-1) + fib(n-2)
  def fib_(n) do
    case n do
      0 -> 0
      1 -> 1
      n -> fib_(n-1) + fib(n-2)
    end
  end
end

defmodule GCD do
  def gcd(x, 0), do: x
  def gcd(x, y), do: gcd(y, rem(x, y))
end
#IO.puts GCD.gcd(100,75)

#============================================================================#
#============================================================================#
#============================================================================#

# Euler 2 
#even? = &(rem(&1, 2) == 0)
#IO.puts Enum.map(1..35, &Fib.fib(&1)) |> Stream.filter(&(&1<4_000_000)) |> Stream.filter(even?) |> Enum.sum

defmodule PrimeFactors do
    @moduledoc """
    Inspired by Uncle Bob's algorithm:
    http://butunclebob.com/ArticleS.UncleBob.ThePrimeFactorsKata
    """
 
    @spec generate(integer) :: list
    def generate(n) do
        generate(n, [], 2) |> Enum.sort     
    end 
 
    # The inner "while" cicle
    defp generate(n, prime_factors, candidate) when rem(n, candidate) == 0 do
        generate(div(n, candidate), [candidate|prime_factors], candidate)
    end
 
    # The outer "while" cicle
    defp generate(n, prime_factors, candidate) when n > 1 do
      generate(n, prime_factors, candidate + 1)
    end
 
    defp generate(_n, prime_factors, _candidate), do: prime_factors
end
# Euler 3 
#IO.puts Enum.max(PrimeFactors.generate(13195)) 
#IO.puts Enum.max(PrimeFactors.generate(600851475143))

#============================================================================#
#============================================================================#
#============================================================================#

defmodule Utility do
  def check_palindrome(n), do: to_char_list(n)==Enum.reverse(to_char_list(n))

  def allper(n) do
    permu(n,0,[]) 
      |> Stream.filter(&(Utility.check_palindrome(&1))) 
      |> Enum.at(0) 
  end

  def permu(n,i,list) when i<n do 
    permu(n,i+1,[n*i|list])
  end

  def permu(n,n,list), do: list
end

# Euler 4
#999..100 |> Enum.map(&Utility.allper(&1)) |> Enum.max |> IO.puts 

#============================================================================#
#============================================================================#
#============================================================================#

defmodule Prime do
  def isPrime(n) when n<3, do: true
  def isPrime(n) do
    n-1..2
      |> Enum.filter(&rem(n,&1)==0) 
      |> length==0
  end

  def  allPrime(n,idx\\-1), do: primeList([],Stream.take(2..n,n-1),n,idx)
  defp removeMul(i,list),   do: Stream.filter(list,fn(x) -> rem(x,i)!=0 end)
  defp primeList(prime,list,n,idx) do
    cond do
      length(prime)==idx ->
        List.last(prime)
      List.last(Enum.to_list(Stream.take(list,1))) > :math.sqrt(n) ->
        result = Stream.take(Stream.concat(prime,list), idx)
        List.last(Enum.to_list(result))
      true -> 
        [i] = Enum.to_list(Stream.take(list,1))
        t = Stream.drop(list,1)
        primeList(prime++[i],removeMul(i,t),n,idx)
    end
  end
end


#============================================================================#
#============================================================================#
#============================================================================#

# Euler 5
#minNum = 20..1 |> Enum.filter(&Prime.isPrime(&1)==true) |> Enum.reduce(1, fn(x, acc) -> x * acc end)
#IO.puts 10..1 |> Enum.filter(&rem(2520,&1)!=0) |> length==0
#IO.puts 20..1 |> Enum.filter(&rem(2*2*2*3*minNum,&1)!=0) |> length==0
#IO.puts 2*2*2*3*minNum

#============================================================================#
#============================================================================#
#============================================================================#

# Euler 6
# Formula: (3(n+1)^2*n^2-2n*(n+1)*(2n+1))/12
#IO.puts (3*101*101*100*100-200*101*201)/12

#============================================================================#
#============================================================================#
#============================================================================#

# Euler 7 
# Find the n-th Prime
#IO.puts Prime.allPrime(1_000,168)
#IO.puts Prime.allPrime(1_000_000,1680)
#IO.puts Prime.allPrime(1_000_000,10001)
IO.puts Prime.allPrime(1_000_000,50001)

#============================================================================#
#============================================================================#
#============================================================================#



