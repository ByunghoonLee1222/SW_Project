library ieee;
use ieee.std_logic_1164.all;

entity Final_Project is
	port ( play1, play2 : in std_logic_vector ( 2 downto 0 );
			clk : in std_logic;
			button0,button1 : in std_logic;
			rsf_led1,rsf_led2 : out std_logic;
			
			smcount :out std_logic;
			winflag : out std_logic;
			winner : out std_logic
			 );
end Final_Project;

architecture sample of Final_Project is
		component RSF_1
				port ( play1, play2 : in std_logic_vector ( 2 downto 0 );
				rsf1_start : in std_logic;
				button0 : in std_logic ;
				clk : in std_logic;
				smcount : out std_logic;
				rsf_check1 : out std_logic;
				rsf_led1 : out std_logic;
				winflag : out std_logic );
		end component;
		
		component RSF_2
				port ( play1, play2 : in std_logic_vector ( 2 downto 0 );
			winflag : in std_logic; 
			button1 : in std_logic;
			rsf2_start : in std_logic; -- check1
			clk : in std_logic;
			rsf_check1, rsf_check2 : out std_logic;
			rsf_led2 : out std_logic;
			winner : out std_logic  );
		end component;

signal rsf_check1, rsf_check2 : std_logic := '0';
signal winflag_component : std_logic ;

begin
		u1 : RSF_1 port map (play1, play2, rsf_check1,button0, clk, smcount,rsf_check1,rsf_led1,winflag );


end sample;
