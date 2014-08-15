
# Programs reflect Specification
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

IO.puts Fib.fib_(30)
