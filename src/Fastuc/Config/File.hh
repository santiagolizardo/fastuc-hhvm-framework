<?hh // strict
namespace Fastuc\Config;

class File
{
	const DEFAULT_FILE_EXTENSION = '.hh';

	/**
	 * @var string
	 */
	private string $name;

	/**
	 * @var string
	 */
	private string $basePath;

	/**
	 * @param string $name
	 */
	public function __construct( string $name = null )
	{
		$this->name = $name;
		$this->basePath = __DIR__;
	}

	public function getName() : ?string
	{
		return $this->name;
	}

	/**
	 * @param string $name
	 */
	public function setName( string $name ) : void
	{
		$this->name = $name;
	}

	/**
	 * @return string
	 */
	public function getBasePath() : string
	{
		return $this->basePath;
	}

	/**
	 * @param string $basePath
	 */
	public function setBasePath( string $basePath ) : void
	{
		$this->basePath = $basePath;
	}

	/**
	 * @return string
	 */
	public function getPath() : string
	{
		return $this->basePath . DIRECTORY_SEPARATOR . $this->name . self::DEFAULT_FILE_EXTENSION;
	}

	/**
	 * @return bool
	 */
	public function exists() : bool
	{
		$configPath = $this->getPath();
		return file_exists( $configPath );
	}

	/**
	 * @return mixed
	 */
	public function getValue() : mixed
	{
		$configPath = $this->getPath();
		if( $this->exists() === false )
		{
			throw new Exception( 'Configuration file not found: ' . $configPath );
		}
		return require $configPath;
	}
}

