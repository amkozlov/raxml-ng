#!/bin/bash

POSITIONAL_ARGS=()

WORKERS=X

while [[ $# -gt 0 ]]; do
  case $1 in
    -np|--np)
      RANKS="$2"
      shift # past argument
      shift # past value
      ;;
    -t|--threads)
      THREADS="$2"
      shift # past argument
      shift # past value
      ;;
    -w|--workers)
      WORKERS="$2"
      shift # past argument
      shift # past value
      ;;
    -*|--*)
      echo "Unknown option $1"
      exit 1
      ;;
    *)
      POSITIONAL_ARGS+=("$1") # save positional arg
      shift # past argument
      ;;
  esac
done

let CPU=RANKS*THREADS

echo "C${CPU}___R${RANKS}_T${THREADS}_W${WORKERS}"
