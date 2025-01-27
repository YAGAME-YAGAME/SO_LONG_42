
==========================================================================================================
// FLAGS USED FOR COMPILING MLX42

	The flags `-Wunreachable-code`, `-Ofast`, `-ldl`, `-lglfw`, `-pthread`, and `-lm` are used
	when compiling and linking programs with MLX42.

	`-Wunreachable-code` enables warnings for dead code,
	while `-Ofast` optimizes the program for maximum performance.

	`-ldl` links the dynamic linker library for runtime loading of shared libraries,
	and `-lglfw` links the GLFW library for window management and OpenGL context handling.

	`-pthread` adds multithreading support, and `-lm` links the math library for mathematical functions.
	These flags ensure MLX42 programs are optimized, functional, and linked to necessary dependencies.

	`-framework OpenGL` links the OpenGL framework for graphics rendering,
	and `-framework AppKit` links the AppKit framework for window management on macOS.
	These flags are necessary for MLX42 to handle graphics and GUI functionality on macOS systems.

==========================================================================================================

==========================================================================================================
// MAP VERIFICATIONS

	-> The map is surrounded with walls (1) [ If not return an error]
	-> The map should have at least one collectable (C)
	-> The map should have at least one exit (E)
	-> The map should have at least one player (P)
	-> The map should have a valid way to all the collectables and the exit
	-> The map should have a *.ber file extention

	-? If the map contains a duplicates characters (exit/start), you should display an error message

	[If any misconfiguration of any kind is encountered in the file, the program must exit in a clean way,
		and return "Error\n" followed by an explicit error message of your choice]

	EXIT =>
		-> print "Error\n --- The map should have..."

----------------------------------------------------------------------------------------------------------
// Map Parsing Steps

	a. Read the Map File
		The map is provided as a .ber file.
		Use get_next_line to read the map file line by line.
		Store the map in a 2D array (char **map) for easy access and manipulation.

	b. Validate the Map

		File Format:
			Ensure the file has a .ber extension.
			Ensure the file is readable and not empty.

		Map Structure:
			The map must be rectangular: All lines must have the same length.
			The map must be closed/surrounded by walls:
				The first and last rows must consist entirely of 1s (walls).
				The first and last characters of each row must be 1s.

		Map Content:
			Count the number of P, E, and C characters:
				Exactly one P (player).
				Exactly one E (exit).
				At least one C (collectible).
			Ensure no invalid characters are present (only 0, 1, C, E, P are allowed).

		Path Validation:
			Use a flood-fill algorithm (e.g., DFS or BFS) to check if:
				The player (P) can reach the exit (E).
				The player can collect all collectibles (C).


==========================================================================================================


==========================================================================================================
//Code Structure

	Reading the Map:

		The ft_read_map function reads the map from a file and stores it in the t_map_data structure. It handles errors related to file opening and memory allocation.

	Freeing the Map:

		The free_map function frees the allocated memory for the map.

	Calculating Map Elements:

		The ft_calculate_elements function counts the number of players, collectables, and exits in the map.

	Checking Requirements:

		The ft_check_requirements function ensures that there is exactly one player, at least one collectable, and exactly one exit. It calls ft_map_errors to print appropriate error messages if the requirements are not met.

	Finding the Player:

		The ft_find_pos function locates the player's starting position in the map.

	Flood Fill Algorithm:

		The flood_fill function performs a flood fill algorithm to mark reachable areas of the map starting from the player's position.

	Checking Flood Fill:

		The ft_check_flood function verifies that all collectables and the exit are reachable by checking if any 'C' or 'E' characters remain in the map after the flood fill.

	Checking Path Validity:

		The ft_check_path function creates a copy of the map, performs the flood fill, and checks if all required elements are reachable. It frees the copied map and returns the result.

	Validating the Map:

		The ft_validate_map function performs a series of checks to validate the map:
			It checks if the map is rectangular using ft_check_rectangular.
			It checks if the map is surrounded by walls using ft_check_walls.
			It checks for invalid characters using ft_check_chars.
			It checks the required elements using ft_check_requirements.
			It checks for a valid path using ft_check_path.
==========================================================================================================


==========================================================================================================

// NOW IT'S ADVENTURE'S TIME

	?How to start a new empty window?

		//Initialize the connexion with the mac IO server and create an empty window
			mlx_t *mlx_ptr = mlx_init(int32_t width, int32_t height, const char *title, bool resize);
			if (!mlx_ptr){ ft_printf("Failed to initialize MLX42\n"); return; }

		//We need to leave the window open
			mlx_loop(mlx_ptr);

	That's it!

	?How to put images there?

		// create the image
			mlx_image_t *img = mlx_new_image(mlx_t *mlx, uint32_t width, uint32_t height);
			if (!img) { ft_printf("Failed to create image\n"); return; }

		//push the image to the window
			mlx_image_to_window(mlx_t *mlx, mlx_image_t *img, int32_t x, int32_t y);

==========================================================================================================
