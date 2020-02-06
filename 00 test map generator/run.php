<?php
/*
 * The script is used to create test data of map setting.
 */
class Chunk{
  private $layers = [];

  function __construct() {
    $this->createVoxel();
    $this->createBoundary();
    $this->createGround();
    $this->createArchitecture();
  }

  private function createVoxel(){
    $layer = [];
    for($k=0;$k<100;$k++){
      for($j=0;$j<100;$j++){
        $raw = [];
        for($i=0;$i<100;$i++) {
          $raw[] = "0";
        }
        $layer[] = $raw;
      }
      $this->layers[] = $layer;
    }
  }

  private function createBoundary(){
    for($j=0;$j<100;$j++){
      for($i=0;$i<100;$i++){
        $this->layers[0][$j][$i]='X';
      }
    }
  }

  private function createGround(){
    for($k=1;$k<1+5;$k++){
      for($j=0;$j<100;$j++){
        for($i=0;$i<100;$i++) {
          $this->layers[$k][$j][$i]='1';
        }
      }
    }
  }

  private function createArchitecture(){
    //create truss
    for($j=10;$j<=90;$j++) {
      $this->layers[10][0][$j]='1';
    }

    //create pillar
    for($j=6;$j<10;$j++) {
      $this->layers[$j][0][10] = "1";
      $this->layers[$j][0][90] = "1";
      $this->layers[$j][0][50] = "1";
      $this->layers[$j][0][30] = "1";
      $this->layers[$j][0][20] = "1";
    }
  }

  public function printVoxel(){
    for($k=0;$k<100;$k++){
      for($j=0;$j<100;$j++){
        for($i=0;$i<100;$i++) {
          echo $this->layers[$k][$j][$i];
        }
      }
      echo "\n";
    }
  }
	
}

$chunk =  new Chunk();
$chunk->printVoxel();
