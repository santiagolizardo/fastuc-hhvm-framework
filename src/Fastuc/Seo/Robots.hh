<?hh // strict
namespace Fastuc\Seo;

/**
 * This class creates the content of a robots.txt file dynamically.
 */
class Robots
{
	private Vector<array> $rules;

	/**
	 * @var string
	 */
	private string $sitemapUrl;

	public function __construct()
	{
		$this->rules = new Vector<string>;
		$this->sitemapUrl = null;
	}

	/**
	 * @param string $userAgent
	 * @param bool $allowed
	 * @param string $resource
	 */
	public function addRule( string $userAgent, bool $allowed, string $resource ) : void
	{
		$this->rules->add( array(
			'userAgent' => $userAgent,
			'allowed' => $allowed,
			'resource' => $resource
		) );
	}

	public function getRules() : Vector<array>
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

	public function getSitemapUrl() : ?string
	{
		return $this->sitemapUrl;
	}

	/**
	 * Generates an string containing what you could expect from a /robots.txt file. 
	 *
	 * @return string
	 */
	public function toText() : string
	{
		$lines = new Vector<string>;

		if( null !== $this->sitemapUrl )
		{
			$lines->add( 'Sitemap: ' . $this->sitemapUrl );
		}

		foreach( $this->rules as $rule )
		{
			$lines->add( 'User-agent: ' . $rule['userAgent'] );
			$lines->add( ( $rule['allowed'] ? 'Allow: ' : 'Disallow: ' ) . $rule['resource'] );
		}

		return implode( $lines->toArray(), PHP_EOL );
	}

	/**
	 * @return string
	 */
	public function __toString() : string
	{
		return sprintf( '[ Robots: rules(%d), sitemapUrl(%s) ]', count( $this->rules ), $this->sitemapUrl );
	}
}

