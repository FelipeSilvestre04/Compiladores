`timescale 1ns/1ps

module tb_cpu_fatorial;
    reg clk_50 = 1'b0;
    reg sim_clk = 1'b0;
    reg rst = 1'b0;
    reg [17:0] switches = 18'd5;
    reg btn_in = 1'b0;

    wire led_clock;
    wire [6:0] Hex0;
    wire [6:0] Hex1;
    wire [6:0] Hex2;
    wire [6:0] Hex3;
    wire [6:0] Hex4;
    wire [6:0] Hex5;
    wire [6:0] Hex6;
    wire [6:0] Hex7;
    wire [5:0] switches_leds;
    wire btn_out;
    wire in_sign_out;

    integer cycles = 0;
    integer outputs = 0;

    cpu dut (
        .clk_50(clk_50),
        .rst(rst),
        .switches(switches),
        .btn_in(btn_in),
        .led_clock(led_clock),
        .Hex0(Hex0), .Hex1(Hex1), .Hex2(Hex2), .Hex3(Hex3),
        .Hex4(Hex4), .Hex5(Hex5), .Hex6(Hex6), .Hex7(Hex7),
        .switches_leds(switches_leds),
        .btn_out(btn_out),
        .in_sign_out(in_sign_out)
    );

    always #1 clk_50 = ~clk_50;
    always #5 sim_clk = ~sim_clk;

    initial begin
        force dut.clk = sim_clk;
        force dut.io_read_strobe = 1'b1;
        force dut.io_output_strobe = 1'b1;

        #12 rst = 1'b1;

        repeat (500) begin
            @(posedge sim_clk);
            cycles = cycles + 1;

            if (dut.WriteToIO) begin
                outputs = outputs + 1;
                $display("RTL_OUTPUT %0d", dut.rs1_data);
                if (dut.rs1_data !== 32'd120) begin
                    $display("RTL_FAIL output inesperado");
                    $finish;
                end
            end

            if (dut.Halt) begin
                if (outputs == 1) begin
                    $display("RTL_PASS cycles=%0d", cycles);
                end
                else begin
                    $display("RTL_FAIL quantidade de saidas=%0d", outputs);
                end
                $finish;
            end
        end

        $display("RTL_FAIL timeout");
        $finish;
    end
endmodule
