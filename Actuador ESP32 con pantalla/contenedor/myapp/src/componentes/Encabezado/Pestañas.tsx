import './estilo.css'
import type { ReactNode } from 'react';
interface Tip {
 titulo : string[];
 children?: ReactNode;   
}

 

 export function Pesta ({titulo, children }:Tip)
 {
    
  return ( <div className="pesta">
   {titulo.map((ti, index)=>( <div className='pesta-individual' key={index}><p>{ti}</p></div>))}
   <>
   {children}
   </> 

  </div> )
 }
