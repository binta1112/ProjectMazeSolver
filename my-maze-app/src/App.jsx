import React, { useState } from "react";
import Maze from "./components/Maze";
import Controls from "./components/Controls";
import "./styles.css";  // Import du fichier CSS

const App = () => {
  const [maze, setMaze] = useState(() => {
    const newMaze = Array.from({ length: 20 }, () => Array(30).fill(4));
    newMaze[0][0] = 2;    // on predefini la 1ere case comme l'entree
    newMaze[19][29] = 3;  // on predefini la derniere cse comme sortie
    return newMaze;
  });
  const [AlgoChoice,setAlgoChoice] = useState(1);
  const [caseState,setCaseState] = useState(0);     
  const [Entree,setEntree]= useState([0,0]);
  const [Sortie,setSortie]= useState([19,29]);

  
  const ShowPath=(path,grid)=>
  {    
    // Crée une copie du tableau maze pour ne pas modifier l'état directement
    const newMaze = [...grid];
   // On parcourt chaque couple (i, j) dans path
  
  path.forEach(([i, j]) => {
      
    setTimeout(()=>{
      if(!(i==Entree[0]&&j==Entree[1])&&!(i==Sortie[0]&&j==Sortie[1]))
        { setMaze(newMaze);
         newMaze[i][j] = 5;
        
         console.log("hello" ,maze,newMaze)
        }
    },500)  
  });

  console.log(Entree , Sortie );

  // On met à jour l'état de maze avec le nouveau tableau
  setMaze(newMaze);
  }
  const generateMaze = async () => {
    const response = await fetch("http://localhost:8080/generate", {
      method: "GET",
      headers: {
        "Content-Type": "application/json",
      },
      
    })
    const data = await response.json();
    setMaze([...data.maze]);
   // console.log([...data.maze]);
  };

  const solveMaze = async () => {
    console.log(AlgoChoice);
    const mazeData =
    {
       
       algo:AlgoChoice==1?1:2,
       grid:maze
    }
    const response =  await fetch("http://localhost:8080/solve", {
      method: "Post",
      headers: {
        "Content-Type": "application/json",
      },
      body: JSON.stringify(mazeData),
    })
    const data = await response.json();
    //setMaze([...data.maze]);
    console.log(data.steps);
    let time=100;
    const grid = [...maze];
     data.steps.forEach(([i, j],index) => {      
      setTimeout(()=>{
        if(!(i==Entree[0]&&j==Entree[1])&&!(i==Sortie[0]&&j==Sortie[1]))
          { 
            grid[i][j] = 6;
          setMaze([...grid]);
         
          }
          ;
      },time*index) } )
     
      const stepsDuration = time * data.steps.length;
   
    data.path.forEach(([i, j],index) => {      
      setTimeout(()=>{
        if(!(i==Entree[0]&&j==Entree[1])&&!(i==Sortie[0]&&j==Sortie[1]))
          { 
            grid[i][j] = 5;
          setMaze([...grid]);
         
          }
          ;
      },stepsDuration+time*index) } )

  };
  console.log(AlgoChoice);
  return (
    <div className="app">     
      <Controls onGenerate={generateMaze} onSolve={solveMaze} Choice ={setAlgoChoice} ES={setCaseState}/>
      <Maze mazeData={maze} setGrid={setMaze} select={caseState} Entree={setEntree} Sortie={setSortie} />
    </div>
  );
};

export default App;
