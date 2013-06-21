n,a;
main(i)
{
   // i init with 1
   for(scanf("%d",&n);n/i;i+=2){
      n%i||++a; // ++a if n%i
      printf("%d,%d\n",i,a);
   }
   printf("%d",a);
}
