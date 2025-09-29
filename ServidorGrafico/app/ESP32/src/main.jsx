import { StrictMode } from 'react'
import { createRoot } from 'react-dom/client'
import { BrowserRouter } from "react-router-dom";
import { Routes, Route, Link } from "react-router-dom";
import './index.css'
import Home from './Pagina/Home';


createRoot(document.getElementById('root')).render(
  <StrictMode>
    <BrowserRouter>
    <Routes>
    <Route path='/' element = { <Home/>}/>
    </Routes>
    </BrowserRouter>
  </StrictMode>,
)
