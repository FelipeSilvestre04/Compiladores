`timescale 1ns/1ps

module tb_cpu;

    reg CLOCK_50;
    reg [3:0] KEY;
    reg [17:0] SW;
    wire [6:0] HEX0, HEX1, HEX2, HEX3, HEX4, HEX5, HEX6, HEX7;
    wire [17:0] LEDR;
    wire [8:0] LEDG;

    // Instantiate top-level module
    top top_inst (
        .CLOCK_50(CLOCK_50),
        .KEY(KEY),
        .SW(SW),
        .HEX0(HEX0),
        .HEX1(HEX1),
        .HEX2(HEX2),
        .HEX3(HEX3),
        .HEX4(HEX4),
        .HEX5(HEX5),
        .HEX6(HEX6),
        .HEX7(HEX7),
        .LEDR(LEDR),
        .LEDG(LEDG)
    );

    // 50 MHz Clock generator
    always #10 CLOCK_50 = ~CLOCK_50;

    // Internal cpu signals reference
    wire cpu_clk = top_inst.de2_115_inst.cpu_inst.clk;
    wire [31:0] cpu_pc = top_inst.de2_115_inst.cpu_inst.PC;
    wire [31:0] cpu_instrucao = top_inst.de2_115_inst.cpu_inst.instrucao;
    wire cpu_halt = top_inst.de2_115_inst.cpu_inst.Halt;
    wire cpu_in_sig = top_inst.de2_115_inst.cpu_inst.IN_signal;
    wire cpu_stall_in = top_inst.de2_115_inst.cpu_inst.stall_for_input;
    wire cpu_write_io = top_inst.de2_115_inst.cpu_inst.WriteToIO;
    wire [31:0] cpu_io_out = top_inst.de2_115_inst.cpu_inst.io_data_out;

    // Inputs array
    reg [31:0] test_inputs[0:9];
    integer input_idx;

    initial begin
        CLOCK_50 = 0;
        KEY = 4'b1111; // Keys are active-low, initialized to high (unpressed)
        SW = 18'b0;

        test_inputs[0] = 32'd9;
        test_inputs[1] = 32'd2;
        test_inputs[2] = 32'd7;
        test_inputs[3] = 32'd1;
        test_inputs[4] = 32'd8;
        test_inputs[5] = 32'd3;
        test_inputs[6] = 32'd5;
        test_inputs[7] = 32'd0;
        test_inputs[8] = 32'd4;
        test_inputs[9] = 32'd6;
        input_idx = 0;

        $display("\n=============================================");
        $display("[TB] Starting FPGA CPU Simulation");
        $display("=============================================\n");

        // Apply reset
        #50;
        KEY[3] = 0; // Assert reset (active-low)
        #200;
        KEY[3] = 1; // Deassert reset
        $display("[TB] Reset deasserted. Running program...");
    end

    // Input feeder handshake logic
    always @(posedge CLOCK_50) begin
        if (cpu_in_sig && cpu_stall_in) begin
            if (input_idx < 10) begin
                $display("[TB] Feed input[%0d] = %0d on switches", input_idx, test_inputs[input_idx]);
                SW = test_inputs[input_idx][17:0];
                #100;
                KEY[0] = 0; // Press KEY[0] (active-low button for IN handshake)
                #200;
                KEY[0] = 1; // Release KEY[0]
                #200;
                input_idx = input_idx + 1;
            end
        end
    end

    // Monitor OUT instructions
    always @(posedge cpu_clk) begin
        if (cpu_write_io) begin
            $display("[TB] CPU Output (OUT): %0d (displayed on HEX displays)", cpu_io_out);
        end
    end

    // Print CPU states
    always @(posedge cpu_clk) begin
        if (!top_inst.de2_115_inst.cpu_inst.effective_halt) begin
            $display("Time=%0t | PC=%0d | Inst=%b | ra=%0d | sp=%0d | t0=%0d | t1=%0d | t2=%0d", 
                $time, 
                cpu_pc, 
                cpu_instrucao,
                top_inst.de2_115_inst.cpu_inst.banco_inst.registradores[1], // $ra
                top_inst.de2_115_inst.cpu_inst.banco_inst.registradores[2], // $sp
                top_inst.de2_115_inst.cpu_inst.banco_inst.registradores[4], // $t0
                top_inst.de2_115_inst.cpu_inst.banco_inst.registradores[5], // $t1
                top_inst.de2_115_inst.cpu_inst.banco_inst.registradores[6]  // $t2
            );
        end
    end

    // Halt and Dump memory
    always @(posedge cpu_clk) begin
        if (cpu_halt) begin
            $display("\n=============================================");
            $display("[TB] HALT DETECTED! Printing RAM array content:");
            $display("=============================================");
            $display("RAM[0] = %0d", top_inst.de2_115_inst.cpu_inst.ram_inst.ram[0]);
            $display("RAM[1] = %0d", top_inst.de2_115_inst.cpu_inst.ram_inst.ram[1]);
            $display("RAM[2] = %0d", top_inst.de2_115_inst.cpu_inst.ram_inst.ram[2]);
            $display("RAM[3] = %0d", top_inst.de2_115_inst.cpu_inst.ram_inst.ram[3]);
            $display("RAM[4] = %0d", top_inst.de2_115_inst.cpu_inst.ram_inst.ram[4]);
            $display("RAM[5] = %0d", top_inst.de2_115_inst.cpu_inst.ram_inst.ram[5]);
            $display("RAM[6] = %0d", top_inst.de2_115_inst.cpu_inst.ram_inst.ram[6]);
            $display("RAM[7] = %0d", top_inst.de2_115_inst.cpu_inst.ram_inst.ram[7]);
            $display("RAM[8] = %0d", top_inst.de2_115_inst.cpu_inst.ram_inst.ram[8]);
            $display("RAM[9] = %0d", top_inst.de2_115_inst.cpu_inst.ram_inst.ram[9]);
            $display("=============================================");
            $display("RAM[16] (sort parameter offset) = %0d", top_inst.de2_115_inst.cpu_inst.ram_inst.ram[16]);
            $display("RAM[17] (sort parameter offset) = %0d", top_inst.de2_115_inst.cpu_inst.ram_inst.ram[17]);
            $display("RAM[18] (sort parameter offset) = %0d", top_inst.de2_115_inst.cpu_inst.ram_inst.ram[18]);
            $display("RAM[19] (sort parameter offset) = %0d", top_inst.de2_115_inst.cpu_inst.ram_inst.ram[19]);
            $display("RAM[20] (sort parameter offset) = %0d", top_inst.de2_115_inst.cpu_inst.ram_inst.ram[20]);
            $display("RAM[21] (sort parameter offset) = %0d", top_inst.de2_115_inst.cpu_inst.ram_inst.ram[21]);
            $display("RAM[22] (sort parameter offset) = %0d", top_inst.de2_115_inst.cpu_inst.ram_inst.ram[22]);
            $display("RAM[23] (sort parameter offset) = %0d", top_inst.de2_115_inst.cpu_inst.ram_inst.ram[23]);
            $display("RAM[24] (sort parameter offset) = %0d", top_inst.de2_115_inst.cpu_inst.ram_inst.ram[24]);
            $display("RAM[25] (sort parameter offset) = %0d", top_inst.de2_115_inst.cpu_inst.ram_inst.ram[25]);
            $display("=============================================");
            $finish;
        end
    end

    // Safety timeout
    initial begin
        #10000000; // 10ms simulation time limit
        $display("[TB] Error: Simulation timeout!");
        $finish;
    end

endmodule
