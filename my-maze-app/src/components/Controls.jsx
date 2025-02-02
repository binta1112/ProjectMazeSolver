import React from "react";
import "../styles.css";  // Import du fichier CSS

const Controls = ({ onGenerate, onSolve,Choice ,ES}) => {

  
  const UpdateChoice = (event) => {
    const selectedValue = event.target.value; 
      Choice(selectedValue);
    
};
const UpdateES = (event) => {
  const selectedValue = event.target.value; 
    ES(selectedValue);
    //console.log(selectedValue);
};
  return (
    <>
    <div className="flex items-center justify-center min-h-[4.5rem] border-b shadow-gray-600 sm:px-5 px-0">
      <div className="flex items-center lg:justify-between  juster-center w:full sm:w-[52rem] ">
      <h1 className="lg:flex hidden w-[40%] text-1xl pl-1">MazeSolver</h1>

      <div className="flex sm:items-end items-center justify-start sm:justofy-between sm:flex-row flex-col sm:space-y-0 space-y-3 sm:py-0 py-4 sm:space-x-4">
        
        <div className="flex flex-col items-start gap-1">
        

        <select name="" id="" onChange={UpdateChoice}
        className="bg-gray-700 cursor-pointer hover:bg-gray-800 transition ease-in active:ring-0 active:border-0 p-2 min-w-[200px] sm:min-w-full"        
        >
        <option value="1">Dijkstra</option>
        <option value="2">BFS</option>
      </select> 
      </div>
      <button  className="contBtn"onClick={onGenerate}>Generate Maze</button>
           
      <button className="contBtn" onClick={onSolve}

      >Solve Maze</button>
     
      </div>
      </div>
   
      
      
    </div>
   
    <div className="choix grid grid-cols-2 sm:grid-cols-4 gap-2 p-2 bg-gray-800 rounded-md shadow-md">
  <div className="flex flex-col items-center text-xs">
    <span className="text-white font-semibold">Entrée</span>
    <button
      className="w-8 h-8 rounded-full shadow-sm border border-red-500 bg-red-500 hover:bg-red-600 transition duration-300"
      value={1}
      onClick={UpdateES}
      style={{backgroundColor:"red"}}
    />
  </div>

  <div className="flex flex-col items-center text-xs">
    <span className="text-white font-semibold">Sortie</span>
    <button
      className="w-8 h-8 rounded-full shadow-sm border border-blue-500 bg-blue-500 hover:bg-blue-600 transition duration-300"
      value={2}
      onClick={UpdateES}
      style={{backgroundColor:"blue"}}
    />
  </div>

  <div className="flex flex-col items-center text-xs">
    <span className="text-white font-semibold">Mur</span>
    <button
      className="w-8 h-8 rounded-full shadow-sm border border-gray-700 bg-black hover:bg-gray-900 transition duration-300"
      value={3}
      onClick={UpdateES}
      style={{backgroundColor:"black"}}
    />
  </div>

  <div className="flex flex-col items-center text-xs">
    <span className="text-white font-semibold">Chemin</span>
    <button
      className="w-8 h-8 rounded-full shadow-sm border border-gray-300 bg-white hover:bg-gray-200 transition duration-300"
      value={4}
      onClick={UpdateES}
   
    />
  </div>
</div>


   
    </>
  );
};

export default Controls;
