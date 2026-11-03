make && openocd \
  -f interface/stlink.cfg \
  -f target/stm32f1x.cfg \
  -c "adapter speed 1000" \
  -c "program build/firmware.elf verify reset exit"