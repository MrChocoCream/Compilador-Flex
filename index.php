<?php


// exec("flex lexico.l");
// exec("bison -d prueba.y");
// exec("gcc -std=c99 -o analizador lex.yy.c prueba.tab.c")
// exec("gcc -std=c99 -o analizador lex.yy.c prueba.tab.c -L 'C:\Program Files (x86)\GnuWin32\lib\libfl.a' -lfl");

?>

<!DOCTYPE html>
<html>

<head>
    <title>Analizador Léxico</title>
    <style>
        * {
            font-family: "Consolas";
        }

        body {
            font-family: Arial, sans-serif;
            background-color: #f2f2f2;
            margin: 0;
            padding: 0;
        }

        header {
            background-color: #333;
            color: #fff;
            text-align: center;
            padding: 20px;
        }

        .container {
            max-width: 800px;
            margin: 0 auto;
            padding: 20px;
            background-color: #fff;
            box-shadow: 0 0 10px rgba(0, 0, 0, 0.1);
            border-radius: 5px;
            margin-top: 20px;
        }

        form {
            display: flex;
            justify-content: center;
            align-items: center;
        }

        input[type="text"] {
            padding: 10px;
            width: 70%;
            border: 1px solid #ccc;
            border-radius: 3px;
            margin-right: 10px;
        }

        button {
            padding: 10px 20px;
            background-color: #333;
            color: #fff;
            border: none;
            cursor: pointer;
        }

        button:hover {
            background-color: #555;
        }

        .output {
            background-color: #f9f9f9;

            border: 1px solid #ddd;
            border-radius: 3px;
            margin-top: 1rem;
            margin-right: 1rem;


            border-radius: .5rem;
            overflow: hidden;
        }

        .output span {
            display: block;
            width: 100%;
            background: #cdcdcd;
            padding-inline: 5px;
            text-align: center;

        }

        .output table {
            padding: 10px;
            width: 100%;
        }

        .espacio {
            padding-right: 100px;
        }
      
      
    #simbolo th, #simbolo td {
      border: 1px solid #000; /* Grosor y color de los bordes */
      padding: 8px; /* Espaciado interno de las celdas */
      text-align: left; /* Alineación del texto */
    }
    </style>
</head>

<body>
    <header>
        <h1 style="font-size: 24px;">Compilador</h1>
    </header>
    <div class="container">
        <form method="POST">
            <textarea name="texto" id="texto" cols="30" rows="5" placeholder="Ingrese el codigo" style="padding: 10px; width: 70%; border: 1px solid #ccc; border-radius: 3px; margin-right: 10px;"></textarea>
            <div style="display: flex; flex-direction: column;">
                <button type="button" id="analizar" style="padding: 10px 20px; background-color: #333; color: #fff; border: none; cursor: pointer;">Analizar</button>
                <label>Lexico<input checked type="checkbox" id="lex"></label>
                <label>Sintactico<input checked type="checkbox" id="sin"></label>
                <label>Semantico<input checked type="checkbox" id="sem"></label>
                <label>Tabla<input checked type="checkbox" id="tab"></label>
            </div>
        </form>

        <div style="display: grid; grid-template-columns: 1fr 1fr;">
        <div class="output">
            <span>Analisis Lexico</span>
            <table>
                <tbody id="lexico">
                </tbody>
            </table>
        </div>

        <div class="output">
            <span>Analisis Sintactico</span>
            <table>
                <tbody id="sintactico">
                </tbody>
            </table>
        </div>

        <div class="output">
            <span>Analisis Semantico</span>
            <table>
                <tbody id="semantico">
                </tbody>
            </table>
        </div>


        <div class="output">
            <span>Tabla de Simbolos</span>
            <table >
                <tbody id="simbolo">
                </tbody>
            </table>
        </div>
        </div>
    </div>

    <script>
        const textoInput = document.getElementById('texto');
        const analizarButton = document.getElementById('analizar');

        const LexicoDiv = document.getElementById('lexico');
        const SintacticoDiv = document.getElementById('sintactico');
        const SemanticoDiv = document.getElementById('semantico');
        const SimboloDiv = document.getElementById('simbolo');

        const lexCheckbox = document.getElementById('lex');
        const sinCheckbox = document.getElementById('sin');
        const semCheckbox = document.getElementById('sem');
        const tabCheckbox = document.getElementById('tab');

        analizarButton.addEventListener('click', () => {
            const texto = textoInput.value.replace(/\n/g, ' ');
            actualizarResultado(texto);
        });

        textoInput.addEventListener('input', () => {
            const texto = textoInput.value.replace(/\n/g, ' ');
            if(!texto){
                LexicoDiv.innerHTML = '';
                SintacticoDiv.innerHTML = '';
                SemanticoDiv.innerHTML = '';
                SimboloDiv.innerHTML = '';
            }else{
                actualizarResultado(texto);
            }
        });

        function actualizarResultado(texto) {
            // Realizar una solicitud AJAX al servidor PHP para enviar la cadena de texto
            // y recibir los resultados del análisis léxico.
            fetch('analizar.php', {
                    method: 'POST',
                    body: new URLSearchParams({
                        texto
                    }),
                    headers: {
                        'Content-Type': 'application/x-www-form-urlencoded'
                    },
                })
                .then(response => response.text())
                .then(resultados => {
                    console.log(resultados);

                    try {
                        let resultado = JSON.parse(JSON.parse(resultados));
                        console.log('Resultado:', resultado);

                        if (lexCheckbox.checked) {
                            LexicoDiv.innerHTML = '<tr><td class="espacio">Valor</td><td>Token</td> </tr>';
                            resultado.lexico.forEach(token => {
                                LexicoDiv.innerHTML += ` <tr><td>${token.value}</td><td>${token.type}</td> </tr>`;
                            });
                        }else{
                            LexicoDiv.innerHTML = '';
                        }

                        if (sinCheckbox.checked) {
                            SintacticoDiv.innerHTML = '';
                            resultado.sintactico.forEach(token => {
                                SintacticoDiv.innerHTML += ` <tr><td>${token.type}</td> </tr>`;
                            });

                            if (SintacticoDiv.innerHTML.includes("ERROR")) {
                                SintacticoDiv.style.color = 'red';
                            } else {
                                SintacticoDiv.style.color = '';
                            }
                        }else{
                            SintacticoDiv.innerHTML = '';
                        }

                        if (semCheckbox.checked) {
                            SemanticoDiv.innerHTML = '';
                            resultado.errores.forEach(token => {
                                SemanticoDiv.innerHTML += ` <tr><td>${token}</td> </tr>`;
                            });

                            if (SemanticoDiv.innerHTML.includes("ERROR")) {
                                SemanticoDiv.style.color = 'red';
                            } else {
                                SemanticoDiv.style.color = '';
                            }
                        }else{
                            SemanticoDiv.innerHTML = '';
                        }

                        if (tabCheckbox.checked) {
                            SimboloDiv.innerHTML = `<tr style="background: #e1e1e1;"><td >Tipo</td><td>Identificador</td><td>Valor</td> </tr>`;
                            resultado.tabla_simbolos.forEach(token => {
                                SimboloDiv.innerHTML += ` <tr><td >${token.tipo}</td><td >${token.identificador}</td><td >${token.valor}</td> </tr>`;
                            });
                        }else{
                            SimboloDiv.innerHTML = '';
                        }
                        
                        

                    } catch (error) {
                        console.error('Error al convertir la respuesta en un objeto:', error);
                    }
                }).catch(error => {
                    console.error('Error en la solicitud AJAX:', error);
                });
        }
    </script>
</body>

</html>