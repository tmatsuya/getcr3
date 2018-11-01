** Get CR3 register driver **

#How to install

 1. make
 2. sudo make install
 3. reboot


How to run

 1. sudo modprobe getcr3
 2. gcc -o user user.c
 3. ./user or sudo ./user

>  $ ./user  
>  return code(length)=8  CR3=FFFFA4951CA90000  
>  return code(length)=8  CR3=FFFFA4951CA90000  
>  return code(length)=8  CR3=FFFFA4951CA90000  
>  return code(length)=8  CR3=FFFFA4951CA90000  
>  ^C   
>  $ ./user  
>  return code(length)=8  CR3=FFFFA4951AA76000  
>  return code(length)=8  CR3=FFFFA4951AA76000  
>  return code(length)=8  CR3=FFFFA4951AA76000   

