<?php
    $db_host  = "localhost";
    $db_name  = "monitor";
    $db_port  = "5432";
    $db_user  = "postgresql";
    $db_senha = "190125";
    if(!@($conexao=pg_connect("hosrt=$db_host,
                              dbname=$db_name,
                              port=$db_port,
                              user=$db_user,
                              password=$db_senha"))){
        print "conexão failed!";                        
    }else{
        pg_close($conexao);
        print "conexão OK!";
    }

   
?>