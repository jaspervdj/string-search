-- | Simple diff to compare two pipes
--
module Main where

import System.Environment (getArgs)
import Control.Concurrent (forkIO, threadDelay)
import Control.Concurrent.Chan (Chan, newChan, readChan, writeChan)
import System.IO (Handle, hGetLine, openFile, IOMode (ReadMode))
import Control.Monad (forever, when, forM, forM_, replicateM)
import Data.List (nub)

producer :: Handle -> Chan String -> IO ()
producer handle chan = forever $ do
    line <- hGetLine handle
    writeChan chan line
    threadDelay 1

consumer :: [Chan String] -> Integer -> IO ()
consumer chans = go
  where
    go n = do
        heads <- forM chans readChan
        -- when (l1 /= l2) $ putStrLn $ l1 ++ " /= " ++ l2
        when (n `mod` 10 == 0) $
            putStrLn $ show n ++ " comparisons done."
        when (fault heads) $
            putStrLn $ "Failed: " ++ show heads
        go (n + 1)
    fault (x : y : xs) = x /= y || fault (y : xs)
    fault _  = False

main :: IO ()
main = do
    handles <- mapM (flip openFile ReadMode) =<< getArgs
    chans <- replicateM (length handles) newChan
    forM_ (zip handles chans) $ forkIO . uncurry producer
    consumer chans 0
