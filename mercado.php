<?php

	$host = "localhost";
    $user = "pc";
    $senha = "pc";
    $nome_do_banco = "sc_mercado";

    $conn = mysqli_connect($host, $user, $senha, $nome_do_banco);

    $uidd = $_GET["uid"];

    $query = "SELECT * FROM tb_produtos WHERE rfid_cod='$uidd'";
    $sql = mysqli_query($conn, $query);

    while ($row = mysqli_fetch_assoc($sql)) {
    	$id = $row['id'];
        //$rfid = $row['rfid_cod'];
    	$nome = $row['nome'];
    	//$peso_volume = $row['peso_volume_kg_L'];
        //$preco = $row['preco'];
        $cod_setor = $row['cod_setor'];
        $cod_marca = $row['cod_marca'];
    }

    $query_setor = "SELECT * FROM tb_setores WHERE id='$cod_setor'";
    $sql_setor = mysqli_query($conn, $query_setor);

    while ($row_setor = mysqli_fetch_assoc($sql_setor)) {
        $id_setor = $row_setor['id'];
        //$nome_setor = $row_setor['nome'];
    }

    $query_marca = "SELECT * FROM tb_marcas WHERE id='$cod_marca'";
    $sql_marca = mysqli_query($conn, $query_marca);

    while ($row_marca = mysqli_fetch_assoc($sql_marca)) {
        $id_marca = $row_marca['id'];
        //$nome_marca = $row_marca['nome'];
    }

    $arr = array($id, $nome);
    $arr_s = array($id_setor);
    $arr_m = array($id_marca);

    /*$obj = json_encode($arr);
    $obj_s = json_encode($arr_s);
    $obj_m = json_encode($arr_m);*/

    $arr_t = array($arr, $arr_s, $arr_m);

    $obj_t = json_encode($arr_t);

    echo ("$obj_t");
    echo "\n";
?>