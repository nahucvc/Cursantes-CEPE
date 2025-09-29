import React from "react"

interface parametros 
{
    children? : React.ReactNode;
    Titulo?: string;
}

export default function Titulo ( dato: parametros)
{
    return (
    <div className="p-0 m-0 f cl center" style={{boxShadow:'0px 10px 8px #282828ff' ,background:'#393434ff', width:'100%', position:'relative', top:'-4px'}}>
            <h1 className="Titulo" style={{color:'#ffffffc4'}} >{dato.Titulo}</h1>  
    </div>)
}