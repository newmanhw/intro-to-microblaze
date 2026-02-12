module led_ctl(
    input clk,
    input rst,

    input  [1:0]  addr,
    input  [15:0] write_data,   
    output [15:0] read_data,    
    input         write_en,

    output [15:0] led,        
    output [2:0]  rgbA,
    output [2:0]  rgbB
);

    reg [15:0] led_data;
    reg [2:0]  rgbA_data;
    reg [2:0]  rgbB_data;

    assign led  = led_data;
    assign rgbA = rgbA_data;
    assign rgbB = rgbB_data;

    // =========================
    // Write logic
    // =========================
    always @(posedge clk) begin
        if (!rst) begin
            led_data  <= 16'd0;
            rgbA_data <= 3'd0;
            rgbB_data <= 3'd0;
        end else if (write_en) begin
            case (addr)
                2'd0: led_data  <= write_data;        
                2'd1: rgbA_data <= write_data[2:0];
                2'd2: rgbB_data <= write_data[2:0];
                default: ;
            endcase
        end
    end

    // =========================
    // Read logic
    // =========================
    reg [15:0] in_rdata;

    always @(*) begin
        case (addr)
            2'd0: in_rdata = led_data;
            2'd1: in_rdata = {13'd0, rgbA_data};
            2'd2: in_rdata = {13'd0, rgbB_data};
            default: in_rdata = 16'd0;
        endcase
    end

    assign read_data = in_rdata;

endmodule
