export default function LabSelect({ UpdateES }) {
    const options = [
      { value: 1, label: "Entrée" },
      { value: 2, label: "Sortie" },
      { value: 3, label: "Mur" },
      { value: 4, label: "Chemin" },
    ];
  
    return (
      <div className="flex gap-2 p-2 bg-gray-100 rounded-lg shadow-md">
        {options.map((option) => (
          <button
            key={option.value}
            onClick={() => UpdateES({ target: { value: option.value } })}
            className="px-4 py-2 text-sm font-medium rounded-md transition-all duration-200
            bg-white border border-gray-300 hover:bg-blue-500 hover:text-white active:scale-95"
          >
            {option.label}
          </button>
        ))}
      </div>
    );
  }
  