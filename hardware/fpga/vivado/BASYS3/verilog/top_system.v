`timescale 1ns / 1ps
`include "system.vh"

module top_system(
	          input         clk,
	          input         reset,

	          //pwm
	          output 	pwm_output,
	          //gpio
   		  input [15:0] gpio_sw,
   		  output [7:0] gpio_sseg_ca,
   		  output [3:0] gpio_sseg_an,
	          //uart
	          output        uart_txd,
	          input         uart_rxd
		  );

   //
   // RESET MANAGEMENT
   //

   //system reset

   wire                         sys_rst;

   reg [15:0] 			rst_cnt;
   reg                          sys_rst_int;

   always @(posedge clk, posedge reset)
     if(reset) begin
        sys_rst_int <= 1'b0;
        rst_cnt <= 16'hFFFF;
     end else begin
        if(rst_cnt != 16'h0)
          rst_cnt <= rst_cnt - 1'b1;
        sys_rst_int <= (rst_cnt != 16'h0);
     end

   assign sys_rst = sys_rst_int;

   //
   // SYSTEM
   //
   system system
     (
      .clk           (clk),
      .rst           (sys_rst),
      .trap          (trap),
      
      //PWM
      .pwm_output(pwm_output),
      
      //UART
      .uart_txd      (uart_txd),
      .uart_rxd      (uart_rxd),
      .uart_rts      (),
      .uart_cts      (1'b1),
      
      //GPIO
      .gpio_sw		(gpio_sw),
      .gpio_sseg_ca	(gpio_sseg_ca),
      .gpio_sseg_an	(gpio_sseg_an)
      );

endmodule
