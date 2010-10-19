-- | Simple diff to compare two pipes
--
module Main where

import System.Environment (getArgs)
import Control.Concurrent (forkIO)
import Control.Concurrent.Chan (Chan, newChan, readChan, writeChan)
import System.IO (Handle, hGetLine, openFile, IOMode (ReadMode))
import Control.Monad (forever)

producer :: Handle -> Chan String -> IO ()
producer handle chan = forever $ do
    line <- hGetLine handle
    writeChan chan line

consumer :: Chan String -> Chan String -> IO ()
consumer chan1 chan2 = forever $ do
    l1 <- readChan chan1
    l2 <- readChan chan2
    putStrLn $ l1 ++ " ?= " ++ l2

main :: IO ()
main = do
    [file1, file2] <- mapM (flip openFile ReadMode) =<< getArgs
    chan1 <- newChan
    chan2 <- newChan
    _ <- forkIO $ producer file1 chan1
    _ <- forkIO $ producer file2 chan2
    consumer chan1 chan2
