import React from "react";
import "../styles.css";  // Import du fichier CSS

const color = {
  1:"black",//mur
  2:"red",//entree
  3:"blue",//sortie
  4:"white",//chemin
  5:"orange",//chemin vers la sortie
  6:"green",//visite
}

const Maze = (props) => {

 const handleCellClick = (rowIndex, colIndex)=>{
  const maze = [...props.mazeData]
 
  if(props.select==3)
  {
    maze[rowIndex][colIndex] = 1;
    props.setGrid([...maze]);
  }
  if(props.select==4)
    {
      maze[rowIndex][colIndex] = 4;
      props.setGrid([...maze]);
    }
  if(props.select==1&&maze[rowIndex][colIndex]!=1)
  {
   
      maze.map((row, rowInd)=>(
      row.map((cell,colInd)=>(
       maze[rowInd][colInd]= cell===2?4:cell
      )) 
    ))
    maze[rowIndex][colIndex] = 2;
    props.setGrid([...maze]);
    props.Entree([rowIndex,colIndex])
   

  }
  else if(props.select==2&&maze[rowIndex][colIndex]!=1)
  {
    maze.map((row, rowInd)=>(
      row.map((cell,colInd)=>(
       maze[rowInd][colInd]= cell===3?4:cell
      )) 
    ))
    maze[rowIndex][colIndex] = 3;
    props.setGrid([...maze]);
    props.Sortie([rowIndex,colIndex])    
  }
 }
  return (
    <div className="maze-container">
      {props.mazeData.map((row, rowIndex) => (
        <div key={rowIndex} style={{ display: "flex" }}>
          {row.map((cell, colIndex) => (
            <div 
              key={colIndex}
              onClick={() => handleCellClick(rowIndex, colIndex)}
              style={{
                width: "20px",
                height: "20px",
                backgroundColor: color[cell],
                border: "1px solid gray",
                transition: color[cell]==5 ?"background-color 5s ease": "",
              }}
            />
          ))}
        </div>
      ))}
    </div>
  );
};

export default Maze;
