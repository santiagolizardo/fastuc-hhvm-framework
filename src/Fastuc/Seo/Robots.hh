<?hh // strict
namespace Fastuc\Seo;

/**
 * This class creates the content of a robots.txt file dynamically.
 */
class Robots
{
	/**
	 * @var array
	 */
	private array $rules;

	/**
	 * @var string
	 */
	private string $sitemapUrl;

	public function __construct()
	{
		$this->rules = array();
		$this->sitemapUrl = null;
	}

	/**
	 * @param string $userAgent
	 * @param bool $allowed
	 * @param string $resource
	 */
	public function addRule( string $userAgent, bool $allowed, string $resource ) : void
	{
		$this->rules[] = array(
			'userAgent' => $userAgent,
			'allowed' => $allowed,
			'resource' => $resource
		);
	}

	/**
	 * @return array
	 */
	public function getRules() : array
	{
		return $this->rules;
	}

	/**
	 * @param string $sitemapUrl
	 */
	public function setSitemapUrl( string $sitemapUrl ) : void
	{
		$this->sitemapUrl = $sitemapUrl;
	}

	/**
	 * @return string
	 */
	public function getSitemapUrl() : string
	{
		return $this->sitemapUrl;
	}

	/**
	 * Generates an string containing what you could expect from a /robots.txt file. 
	 *
	 * @return string
	 */
	public function dumpToString() : string
	{
		$lines = array();

		if( null !== $this->sitemapUrl )
		{
			$lines[] = 'Sitemap: ' . $this->sitemapUrl;
		}

		foreach( $this->rules as $rule )
		{
			$lines[] = 'User-agent: ' . $rule['userAgent'];
			$lines[] = ( $rule['allowed'] ? 'Allow: ' : 'Disallow: ' ) . $rule['resource'];
		}

		return implode( $lines, PHP_EOL );
	}

	/**
	 * @return string
	 */
	public function __toString() : string
	{
		return sprintf( '[ Robots: rules(%d), sitemapUrl(%s) ]', count( $this->rules ), $this->sitemapUrl );
	}
}

