#!/bin/sh

# Terminate already running bar instances
killall -q polybar

polybar bar >> /tmp/polybar.log 2>&1 &