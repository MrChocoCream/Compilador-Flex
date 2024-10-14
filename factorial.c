int main()
{
    int num;
    int i;
    int fact;
    fact = 1;

    printf("Ingresa un numero para calcular su factorial: ");
    scanf("%d", &num);

    if (num < 0)
    {
        printf("El factorial de numeros negativos no esta definido.\n");
      
    }else{

         for (i = 1; i <= num; ++i)
    {
        fact = fact * i;
    }

    printf("El factorial de %d es: %ld\n", num, fact);

    }   
}