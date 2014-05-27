<?hh // strict
namespace Fastuc\Url;

class Statics
{
	/**
	 * @var array
	 */
	private array $urls;

	public function __construct()
	{
		$this->urls = array(
			'base' => '',
			'scripts' => '',
			'images' => '',
			'styles' => '',
		);

		$configFile = new \Fastuc\Config\File( 'statics' );
		if( $configFile->exists() )
		{
			$this->urls = $configFile->getValue();
		}
	}

	/**
	 * @param string $resource
	 * @return string
	 */
	public function getBase( string $resource ) : string
	{
		return $this->urls['base'] . $resource;
	}

	/**
	 * @param string $resource
	 * @return string
	 */
	public function getScript( string $resource ) : string
	{
		return $this->urls['scripts'] . $resource;
	}

	/**
	 * @param string $resource
	 * @return string
	 */
	public function getImage( string $resource ) : string
	{
		return $this->urls['images'] . $resource;
	}

	/**
	 * @param string $resource
	 * @return string
	 */
	public function getStyle( string $resource ) : string
	{
		return $this->urls['styles'] . $resource;
	}
}

