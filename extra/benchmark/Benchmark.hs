-- | Benchmarking code
--
{-# LANGUAGE ForeignFunctionInterface #-}
module Main where

import Control.Monad (forM_, mapM, sequence)
import Control.Applicative ((<$>))
import Foreign
import Foreign.C
import Foreign.C.String
import System.Environment (getProgName)
import Criterion.Main

foreign import ccall "search" c_search :: CInt -> Ptr CString -> IO CInt

main = do
    -- Allocate the arguments
    argv <- mapM newCAString =<< sequence [getProgName, getLine, getLine]
    c_argv <- newArray argv

    -- Run criterion
    defaultMain [bench "C main function" $ c_search 3 c_argv]

    -- Free the arguments
    forM_ argv free
    free c_argv

    return ()
