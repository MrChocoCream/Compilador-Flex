<?php




if ($_SERVER["REQUEST_METHOD"] == "POST" && $_POST["texto"] != '') {  


   $texto = $_POST["texto"];

   $analisis = shell_exec('echo  "---'.$texto.'---"  | .\analizador.exe 2>&1');
  
   header('Content-Type: application/json');
   echo json_encode($analisis);
}










?>
