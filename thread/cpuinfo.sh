for path in /sys/devices/system/cpu/cpu*/cache/index*/
do
  echo $path;
  echo -n "Level: "; cat $path/level;
  echo -n "Type: "; cat $path/type;
  echo -n "Size: "; cat $path/size;
  echo -n "Cache line size: "; cat $path/coherency_line_size;
  echo -n "Associativity: "; cat $path/ways_of_associativity;
done
