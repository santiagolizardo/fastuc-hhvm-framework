<?hh // strict
namespace Fastuc\View;

class Metadata
{
	public static function fillView( \Fastuc\View\Base $view, string $section, Map<string, mixed> $params = Map<string, mixed> {}, string $basePath = null ) : void
	{
		$metadataConfig = new \Fastuc\Config\File( 'metadata' );
		if( $basePath )
		{
			$metadataConfig->setBasePath( $basePath );
		}

		$metadata = $metadataConfig->getValue();

		if( !isset( $metadata[ $section ] ) )
		{
			return;
		}

		$metadata = $metadata[ $section ];

		if( isset( $metadata['title'] ) )
		{
			$title = $metadata['title']( $params );
			$view->setTitle( $title );
		}

		if( isset( $metadata['description'] ) )
		{
			$description = $metadata['description']( $params );
			$view->setMeta( 'description', $description );
		}

		if( isset( $metadata['keywords'] ) )
		{
			$keywords = $metadata['keywords']( $params );
			$view->setMeta( 'keywords', $keywords );
		}
	}
}

