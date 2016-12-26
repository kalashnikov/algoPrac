# Elixir

- [Get Started](http://elixir-lang.org/getting_started/)
- [CheatSheet](http://media.pragprog.com/titles/elixir/ElixirCheat.pdf)
- [Awesome Elixir](https://github.com/h4cc/awesome-elixir)
- [Learn Elixir in Y Minute](http://learnxinyminutes.com/docs/elixir/)
- [Starting with Elixir](http://victorarias.com.br/2013/09/15/starting-with-elixir.html)

[TOC]

------

## Anonymous functions

```
iex> add_two = fn a -> add.(a, 2) end
#Function<6.71889879/1 in :erl_eval.expr/5>
iex> add_two.(2)
4
iex> x = 42
42
iex> (fn -> x = 0 end).()
0
iex> x
42
iex> f = fn
...>   x, y when x > 0 -> x + y
...>   x, y -> x * y
...> end
#Function<12.71889879/2 in :erl_eval.expr/5>
iex> f.(1, 3)
4
iex> f.(-1, 3)
-3
```

------

## Pattern matching

```
iex> {a, b, c} = {:hello, "world", 42}
{:hello, "world", 42}
iex> [head | tail] = [1, 2, 3]
[1, 2, 3]
iex> head
1
iex> tail
[2, 3]
iex> {x, ^x} = {2, 1}
{2, 1}
iex> x
2
iex> {x, ^x} = {2, 1}
{2, 1}
iex> x
2
iex> [h | _] = [1, 2, 3]
[1, 2, 3]
iex> h
1
```

------

## Conditional Block

```
iex> cond do
...>   2 + 2 == 5 ->
...>     "This is never true"
...>   2 * 2 == 3 ->
...>     "Nor this"
...>   true ->
...>     "This is always true (equivalent to else)"
...> end
iex> if nil do
...>   "This won't be seen"
...> else
...>   "This will"
...> end
"This will"
iex> if true, do: 1 + 2
3
iex> if false, do: :this, else: :that
:that
iex> is_number(if true do
...>  1 + 2
...> end)
true
```

------

## Sorting Priority

```
number < atom < reference < functions < port < pid < tuple < maps < list < bitstring
```

------

## Container

- List Operation

```
iex> [1, 2, 3] ++ [4, 5, 6]
[1, 2, 3, 4, 5, 6]
iex> [1, true, 2, false, 3, true] -- [true, false]
[1, 2, 3, true]
iex> list = [1,2,3]
iex> hd(list)
1
iex> tl(list)
[2, 3]
iex> tuple = {:ok, "hello"}
{:ok, "hello"}
iex> elem(tuple, 1)
"hello"
iex> tuple_size(tuple)
2
```

- `Key List`

```
iex> list = [{:a, 1}, {:b, 2}]
[a: 1, b: 2]
iex> list == [a: 1, b: 2]
true
iex> list[:a]
1
```

- `map`

```
iex> map = %{:a => 1, 2 => :b}
%{2 => :b, :a => 1}
iex> map[:a]
1
iex> map[2]
:b
iex> map = %{:a => 1, 2 => :b}
%{:a => 1, 2 => :b}
iex> map.a
1
iex> %{map | :a => 2}
%{:a => 2, 2 => :b}
iex> %{map | :c => 3}
** (ArgumentError) argument error
```

- In Elixir, both `keyword lists` and `maps` are called dictionaries. 
- In other words, a `dictionary` is like an interface (we call them behaviours in Elixir) and both keyword lists and maps modules implement this interface.

```
iex> keyword = []
[]
iex> map = %{}
%{}
iex> Dict.put(keyword, :a, 1)
[a: 1]
iex> Dict.put(map, :a, 1)
%{a: 1}
```

------

## Modules

```
defmodule Math do
  def sum(a, b) do
    a + b
  end
end
```

- This will generate a file named `Elixir.Math.beam` containing the bytecode for the defined module.
- `Elixir` projects are usually organized into three directories:
  - `ebin` - contains the compiled bytecode
  - `lib` - contains elixir code (usually .ex files)
  - `test` - contains tests (usually .exs files)
- `Elixir` file extension `.ex`, Elixir also supports `.exs` files for scripting. Elixir treats both files exactly the same way, the only difference is in intention. `.ex` files are meant to be compiled while `.exs` files are used for scripting, without the need for compilation.
- Private function

```
defmodule Math do
  def sum(a, b) do
    do_sum(a, b)
  end

  defp do_sum(a, b) do
    a + b
  end
end

Math.sum(1, 2)    #=> 3
Math.do_sum(1, 2) #=> ** (UndefinedFunctionError)
```

- The &1 represents the first argument passed into the function. &(&1+1) above is exactly the same as fn x -> x + 1 end. 

```
iex> fun = &(&1 + 1)
#Function<6.71889879/1 in :erl_eval.expr/5>
iex> fun.(1)
2
```

- Default value

```
defmodule Concat do
  def join(a, b, sep \\ " ") do
    a <> sep <> b
  end
end

IO.puts Concat.join("Hello", "world")      #=> Hello world
IO.puts Concat.join("Hello", "world", "_") #=> Hello_world
```

- Multiple default value recommend to declare definition first

```
defmodule Concat do
  def join(a, b \\ nil, sep \\ " ")

  def join(a, b, _sep) when nil?(b) do
    a
  end

  def join(a, b, sep) do
    a <> sep <> b
  end
end

IO.puts Concat.join("Hello", "world")      #=> Hello world
IO.puts Concat.join("Hello", "world", "_") #=> Hello_world
IO.puts Concat.join("Hello")               #=> Hello
```

------

## Recursion

- Use [`Enum` module](http://elixir-lang.org/docs/stable/elixir/Enumerable.html)

```
iex> Enum.reduce([1, 2, 3], 0, fn(x, acc) -> x + acc end)
6
iex> Enum.map([1, 2, 3], fn(x) -> x * 2 end)
[2, 4, 6]
iex> Enum.map(%{1 => 2, 3 => 4}, fn {k, v} -> k * v end)
[2, 12]
iex> Enum.map(1..3, fn x -> x * 2 end)
[2, 4, 6]
```

- Use capture syntax

```
iex> Enum.reduce([1, 2, 3], 0, &+/2)
6
iex> Enum.map([1, 2, 3], &(&1 * 2))
[2, 4, 6]
```

- [Stream module](http://elixir-lang.org/docs/stable/elixir/Stream.html)

```
iex> 1..100_000 |> Stream.map(&(&1 * 3))
#Stream<1..100_000, funs: [#Function<34.16982430/1 in Stream.map/2>]>
iex> 1..100_000 |> Stream.map(&(&1 * 3)) |> Stream.filter(odd?)
#Stream<1..100_000, funs: [...]>
iex> stream = Stream.cycle([1, 2, 3])
#Function<15.16982430/2 in Stream.cycle/1>
iex> Enum.take(stream, 10)
[1, 2, 3, 1, 2, 3, 1, 2, 3, 1]
```

- Another interesting function is `Stream.resource/3` which can be used to wrap around resources, guaranteeing they are opened right before enumeration and closed afterwards, even in case of failures. For example, we can use it to stream a file:

```
iex> stream = File.stream!("path/to/file")
#Function<18.16982430/2 in Stream.resource/3>
iex> Enum.take(stream, 10)
```

------

## [Process](http://elixir-lang.org/docs/stable/elixir/Process.html)

- In `Elixir`, all code runs inside processes. Processes are isolated from each other, run concurrent to one another and communicate via message passing. Processes are not only the basis for concurrency in Elixir, but they also provide the means for building distributed and fault-tolerant programs.
- Process and links play an important role when building fault-tolerant systems. In Elixir applications, we often link our processes to supervisors which will detect when a process die and start a new process in its place. This is only possible because processes are isolated and don't share anything by default. And if processes are isolated, there is no way a failure in a process will crash or corrupt the state of another.
- `spawn`, `send`, `self()`, `receive`: When a message is sent to a process, the message is stored in the process mailbox. The `receive/1` block goes through the current process mailbox searching for a message that matches any of the given patterns.

```
iex> parent = self()
#PID<0.41.0>
iex> spawn fn -> send(parent, {:hello, self()}) end
#PID<0.48.0>
iex> receive do
...>   {:hello, pid} -> "Got hello from #{inspect pid}"
...> end
"Got hello from #PID<0.48.0>"
```

- `flush()`: It flushes and prints all the messages in the mailbox.

```
iex> send self(), :hello
:hello
iex> flush()
:hello
```

------

## IO

- [File](http://elixir-lang.org/docs/stable/elixir/File.html)

```
iex> {:ok, file} = File.open "hello", [:write]
{:ok, #PID<0.47.0>}
iex> IO.binwrite file, "world"
:ok
iex> File.close file
:ok
iex> File.read "hello"
{:ok, "world"}
iex> {:ok, file} = File.open "another", [:write, :utf8]
{:ok, #PID<0.48.0>}
```

- Raise Error when not reading file

```
case File.read(file) do
  {:ok, body} -> # handle ok
  {:error, r} -> # handle error
end
File.read!(file)
```

- Erlang Interop

```
:io.format("~.2f~n", [5.126])
# => 5.13
# => :ok

# module 'io' from Erlang's stdlib is accessible through an atom with the same name
# so, as you can imagine, there is an io module with the function format in it :)
```

------

### Module

- They serve to annotate the module, often with information to be used by the user or the VM.
- They work as constants.

```
defmodule MyServer do
  @my_data 14
  def first_data, do: @my_data
  @my_data 13
  def second_data, do: @my_data
end

MyServer.first_data #=> 14
MyServer.second_data #=> 13
```

- They work as a temporary module storage to be used during compilation.

------

### Record

```
defrecord Person, first_name: nil, last_name: nil, age: nil, country: "Brazil"

person = Person.new first_name: "Victor", last_name: "Arias", age: 26
# => Person[first_name: "Victor", last_name: "Arias", age: 26, country: "Brazil"]

Person[first_name: "Victor", last_name: "Arias", country: "Sweden"] # <- compile time!
# => Person[first_name: "Victor", last_name: "Arias", age: nil, country: "Sweden"]

# a record is just a tuple starting with a module
# so the following tuple declaration works as a record creation
# exactly as Person.new ...
another_person = {Person, "Victor", "Arias", 26, "Brazil"}
# => Person[first_name: "Victor", last_name: "Arias", age: 26, country: "Brazil"]
```

------

### Sigil

- The most common sigil in Elixir is `~r` for regular expressions:

```
iex> "HELLO" =~ ~r/hello/
false
iex> "HELLO" =~ ~r/hello/i
true
```

- The `~s` sigil is used to generate strings, similar to double quotes:

```
iex> ~s(this is a string with "quotes")
"this is a string with \"quotes\""
```

- While `~c` is used to generate char lists:

```
iex> ~c(this is a string with "quotes")
'this is a string with "quotes"'
```

- The `~w` sigil is used to generate a list of words separated by white space:

```
iex> ~w(foo bar bat)
["foo", "bar", "bat"]
```

- The `~w` sigil also accepts the `c`, `s` and `a` modifiers (for char lists, strings and atoms, respectively) to choose the format of the result:

```
iex> ~w(foo bar bat)a
[:foo, :bar, :bat]
```

------


