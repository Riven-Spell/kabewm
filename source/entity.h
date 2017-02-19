class Entity
{
	public:
		struct { float x, y } position;
		unsigned static int last_used_id;
		unsigned int id;
		int current_frame;
		std::vector<unsigned char> frames;
		st_spritesheet *spritesheet;
		virtual void render_next_frame(int framecount);
		Entity(st_spritesheet *spritesheet, size_t frames_len, int *frames);
}
