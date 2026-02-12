library ieee;
use ieee.std_logic_1164.all;

entity my_timer is
port(
    clk : in std_logic;
    pulse : out std_logic
);
end my_timer;

architecture bhv of my_timer is 
    signal cmp : integer range 0 to 100_000_000;
begin
    process(clk)
    begin
        if rising_edge(clk) then
            cmp <= cmp + 1;
            pulse <= '0';
            if cmp = 100_000_000 then
                cmp <= 0;
                pulse <= '1';
            end if;
        end if;
    end process;
end bhv;