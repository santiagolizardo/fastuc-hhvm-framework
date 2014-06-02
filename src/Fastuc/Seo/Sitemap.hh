<?hh // strict
namespace Fastuc\Seo;

/**
 * This class creates XML sitemaps dynamically.
 */
class Sitemap
{
	const FREQ_HOURLY = 'hourly';
	const FREQ_DAILY = 'daily';
	const FREQ_WEEKLY = 'weekly';
	const FREQ_ALWAYS = 'always';

	private Vector<string> $validFrequencies;
	private Vector<SitemapUrl> $urls;

	public function __construct()
	{
		$this->validFrequencies = [ self::FREQ_HOURLY, self::FREQ_DAILY, self::FREQ_WEEKLY, self::FREQ_ALWAYS ];
		$this->urls = new Vector<SitemapUrl>;
	}

	public function addUrl( SitemapUrl $url ) : void
	{
		if( !in_array( $url->getChangeFrequency(), $this->validFrequencies ) )
		{
			throw new \Exception( 'Invalid frequency: ' . $url->getChangeFrequency() );
		}

		$this->urls->add( $url );
	}

	public function getUrls() : Vector<SitemapUrl>
	{
		return $this->urls;
	}

	public function toXml() : string
	{
		$doc = new \DomDocument( '1.0', 'utf-8' );
		$doc->formatOutput = true;

		$urlsetNode = $doc->createElement( 'urlset' );
		$urlsetNode->setAttribute( 'xmlns', 'http://www.sitemaps.org/schemas/sitemap/0.9' );
		$urlsetNode->setAttribute( 'xmlns:xsi', 'http://www.w3.org/2001/XMLSchema-instance' );
		$urlsetNode->setAttribute( 'xsi:schemaLocation', 'http://www.sitemaps.org/schemas/sitemap/0.9 http://www.sitemaps.org/schemas/sitemap/0.9/sitemap.xsd' );

		foreach( $this->urls as $url )
		{
			$urlNode = $doc->createElement( 'url' );
			$urlNode->appendChild( $doc->createElement( 'loc', $url->getLocation() ) );
			$urlNode->appendChild( $doc->createElement( 'changefreq', $url->getChangeFrequency() ) );
			$urlNode->appendChild( $doc->createElement( 'priority', $url->getPriority() ) );
			$urlsetNode->appendChild( $urlNode );
		}

		$doc->appendChild( $urlsetNode );
		
		return $doc->saveXml();
	}

	/**
	 * @return string
	 */
	public function __toString() : string
	{
		return sprintf( '[ Sitemap: urls(%d) ]', $this->urls->count() );
	}
}

