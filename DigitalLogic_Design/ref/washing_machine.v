module washing_machine(
  input reset,//turn on/off
  input start_pause,//pause/continue
  input mode_change,//mode change

  output power,//power
  output running,//sign of start

  output xi,
  output piao,
  output tuo,

  output in,
  output out,

  output buzzer,

  output [6:0] seg,
  output [7:0] an
  );

  reg mode;//change between six modes
  reg weight;//change between three kinds of weight

  wire clk_N;

  divider clk_div(clk,clk_N);
  
endmodule
