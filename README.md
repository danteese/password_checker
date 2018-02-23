# Password Checker

*Versión 1.0*



> Las contraseñas son como la ropa interior: no dejes que otros las vean, cámbialas con frecuencia y no las compartas con desconocidos.
>
> ***Chris Pirillo***



Programa que da el porcentaje de seguridad de una contraseña ingresada desde la línea de comandos. **Ejemplo:** 

```
$ ./passcheck HolaMundo!

Password coverage: HolaMundo!

           Test | Status
      UPPERCASE | [OK]
      lowercase | [OK]
         digits | [FAILED]
      special c | [OK]
      min c > 8 | [OK]
 No App in dict | [OK]

* La aparición en el diccionario reduce puntos.
El porcentaje de seguridad es:
[********************] 5/6 (83.33% Segura)

Recomendaciones
* Usar dígitos podría aumentarlo hasta dos semanas.

```

Utiliza un diccionario obtenido del siguiente repo: [diccionario](https://raw.githubusercontent.com/danielmiessler/SecLists/master/Passwords/10_million_password_list_top_1000.txt).

## What is in the box?

Para instalar, es más que suficiente ejecutar:

```
$ make
```

***Es necesario tener GCC.***

