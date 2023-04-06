-- configure GPIO4 as output
gpio.mode(4, gpio.OUTPUT)

-- loop to blink the LED
while true do
  -- blink the LED 3 times
  for i=1,3 do
    gpio.write(4, gpio.HIGH)
    tmr.delay(500000) -- delay for 500 milliseconds
    gpio.write(4, gpio.LOW)
    tmr.delay(500000) -- delay for 500 milliseconds
  end
  
  -- wait for 10 seconds
  tmr.delay(10000000) -- delay for 10000 milliseconds (10 seconds)
  
  -- blink the LED 3 times again
  for i=1,3 do
    gpio.write(4, gpio.HIGH)
    tmr.delay(500000) -- delay for 500 milliseconds
    gpio.write(4, gpio.LOW)
    tmr.delay(500000) -- delay for 500 milliseconds
  end
  
  -- wait for 10 seconds again
  tmr.delay(10000000) -- delay for 10000 milliseconds (10 seconds)
end
