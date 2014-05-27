<?hh // strict
namespace Fastuc\Config;

class File
{
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

		// @TODO: Remove references to APP_PATH.
		if( defined( 'CONFIG_PATH' ) )
		{
			$this->setBasePath( CONFIG_PATH );
		} else if ( defined ( 'APP_PATH' ) ) 
		{
			$this->setBasePath( APP_PATH . DIRECTORY_SEPARATOR . 'config' );
		}
	}

	/**
	 * @return string
	 */
	public function getName() : string
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
		return $this->basePath . DIRECTORY_SEPARATOR . $this->name . '.php';
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

